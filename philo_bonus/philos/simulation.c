/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:11 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/27 14:04:11 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				sem_t *sim_end, sem_t *fork_lock);
static void	monitor_threads(t_philosopher *philo_list);
// static void	kill_processes(t_philosopher *philo_list);
void		*monitor_fed(void *param);

/// @brief Handles the simulation of the philos
/// @param philo_list 
/// @return 
int	simulation(t_philosopher *philo_list)
{
	sem_t			*print_lock;
	sem_t			*fork_lock;
	sem_t			*sim_end;
	t_philosopher	*current;

	print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);
	sim_end = sem_open("/sim_end", O_CREAT | O_EXCL, 0644, 1);
	fork_lock = sem_open("/fork_lock", O_CREAT | O_EXCL, 0644,
			philo_list->philo_var.num_of_philo / 2);
	sem_wait(print_lock);
	if (create_threads(philo_list, print_lock, sim_end, fork_lock) != 0)
		return (1);
	sem_post(print_lock);
	monitor_threads(philo_list);
	sem_close(philo_list->fork_lock);
	sem_close(philo_list->print_lock);
	sem_close(philo_list->sim_end);
	sem_close(philo_list->fully_fed);
	current = philo_list;
	while (current != NULL)
	{
		kill(current->pro_id, SIGKILL);
		current = current->next;
	}
	return (0);
}

// static void	kill_processes(t_philosopher *philo_list)
// {
// 	t_philosopher	*current;

// 	current = philo_list;
// 	while (current != NULL)
// 	{
// 		kill(current->pro_id, 15);
// 		current = current->next;
// 	}
// }

/// @brief Checks if a philo has dies or all have eaten enough
/// @param philo_list 
static void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;
	pthread_t		check_fed;

	current = philo_list;
	if (pthread_create(&check_fed, NULL, monitor_fed, current) != 0)
		return ;
	wait_ms(current->philo_var.time_to_die);
	sem_wait(current->sim_end);
	sem_wait(current->sim_end);
	philo_list->isdead = true;
	sem_post(current->fully_fed);
	usleep(100);
	pthread_detach(check_fed);
	wait_ms(philo_list->philo_var.time_to_eat
		+ philo_list->philo_var.time_to_sleep);
}

void	*monitor_fed(void *param)
{
	t_philosopher	*philo;
	int				is_fed;

	is_fed = 0;
	philo = (t_philosopher *)param;
	if (philo->philo_var.num_of_philo == -2)
		return (0);
	sem_wait(philo->fully_fed);
	while (is_fed < philo->philo_var.num_of_philo)
	{
		sem_wait(philo->fully_fed);
		if (philo->isdead == true)
			return (0);
		is_fed++;
	}
	sem_wait(philo->print_lock);
	sem_post(philo->sim_end);
	wait_ms(philo->philo_var.time_to_eat
		+ philo->philo_var.time_to_sleep + 1000);
	sem_post(philo->print_lock);
	return (0);
}

/// @brief IStarts the threads
/// @param philo_list 
/// @param print_lock blocks the threads at the start, blocks printing
/// @return 
static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				sem_t *sim_end, sem_t *fork_lock)
{
	t_philosopher	*current;
	sem_t			*fully_fed;
	struct timeval	start_time;

	fully_fed = sem_open("/fully_fed", C | E, 0644, 1);
	current = philo_list;
	start_time = get_start_time();
	start_time.tv_sec++;
	while (current != NULL)
	{
		sem_unlink(current->var_lock_name);
		current->var_lock = sem_open(current->var_lock_name, C | E, 0644, 1);
		current->print_lock = print_lock;
		current->sim_end = sim_end;
		current->fork_lock = fork_lock;
		current->fully_fed = fully_fed;
		current->main_start = &start_time;
		current->pro_id = fork();
		if (current->pro_id == -1)
			return (printf("Fork fail\n"), 1);
		if (current->pro_id == 0)
			philosopher(current);
		current = current->next;
	}
	return (0);
}
