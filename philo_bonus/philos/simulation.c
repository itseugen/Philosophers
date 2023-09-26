/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:11 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 20:25:22 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				sem_t *sim_end, sem_t *fork_lock);
static void	monitor_threads(t_philosopher *philo_list);
static void	set_threads_to_dead(t_philosopher *philo_list);

/// @brief Handles the simulation of the philos
/// @param philo_list 
/// @return 
int	simulation(t_philosopher *philo_list)
{
	sem_t			*print_lock;
	sem_t			*fork_lock;
	sem_t			*sim_end;

	print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);
	sim_end = sem_open("/sim_end", O_CREAT | O_EXCL, 0644, 1);
	fork_lock = sem_open("/fork_lock", O_CREAT | O_EXCL, 0644,
			philo_list->philo_var.num_of_philo / 2);
	if (print_lock == SEM_FAILED || fork_lock == SEM_FAILED)
		return (printf("sem open (sim)\n"), 1);
	sem_wait(print_lock);
	if (create_threads(philo_list, print_lock, sim_end, fork_lock) != 0)
		return (1);
	sem_post(print_lock);
	monitor_threads(philo_list);
	set_threads_to_dead(philo_list);
	sem_post(print_lock);
	sem_close(fork_lock);
	sem_close(print_lock);
	sem_close(sim_end);
	return (0);
}

/// @brief Checks if a philo has dies or all have eaten enough
/// @param philo_list 
static void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	wait_ms(current->philo_var.time_to_die);
	sem_wait(current->sim_end);
	sem_wait(current->sim_end);
}

/// @brief IStarts the threads
/// @param philo_list 
/// @param print_lock blocks the threads at the start, blocks printing
/// @return 
static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				sem_t *sim_end, sem_t *fork_lock)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		current->var_lock = sem_open(current->var_lock_name,
				O_CREAT | O_EXCL, 0644, 1);
		if (current->var_lock == SEM_FAILED)
			return (printf("sem open\n"), 1);
		current->print_lock = print_lock;
		current->sim_end = sim_end;
		current->fork_lock = fork_lock;
		current->pro_id = fork();
		if (current->pro_id == -1)
			return (printf("Fork fail\n"), 1);
		if (current->pro_id == 0)
			philosopher(current);
		current = current->next;
	}
	return (0);
}

static void	set_threads_to_dead(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		kill(current->pro_id, 0);
	}
}
