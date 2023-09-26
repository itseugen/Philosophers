/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:11 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 16:05:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				struct timeval *main_start, sem_t *fork_lock);
static void	monitor_threads(t_philosopher *philo_list);
static void	set_threads_to_dead(t_philosopher *philo_list);
static void	join_threads(t_philosopher *philo_list);

/// @brief Handles the simulation of the philos
/// @param philo_list 
/// @return 
int	simulation(t_philosopher *philo_list)
{
	sem_t			print_lock;
	sem_t			fork_lock;
	struct timeval	main_start;

	print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);
	fork_lock = sem_open("/fork_lock", O_CREAT | O_EXCL, 0644,
			philo_list->philo_var.num_of_philo / 2);
	if (print_lock == SEM_FAILED || fork_lock == SEM_FAILED)
		return (printf("sem open\n"), 1);
	sem_wait(&print_lock);
	if (create_threads(philo_list, &print_lock, &main_start, &fork_lock) != 0)
		return (1);
	main_start = get_start_time();
	sem_post(&print_lock);
	monitor_threads(philo_list);
	set_threads_to_dead(philo_list);
	sem_wait(&print_lock);
	join_threads(philo_list);
	sem_close(&print_lock);
	return (0);
}

/// @brief Checks if a philo has dies or all have eaten enough
/// @param philo_list 
static void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	wait_ms(current->philo_var.time_to_die);
	while (1)
	{
		starving(current);
		sem_wait(&current->var_lock);
		if (current->isdead == true)
		{
			sem_post(&current->var_lock);
			break ;
		}
		sem_post(&current->var_lock);
		if (has_eaten_enough(philo_list) == true)
		{
			sem_wait(current->print_lock);
			break ;
		}
		current = current->next;
		if (current == NULL)
			current = philo_list;
	}
}

/// @brief IStarts the threads
/// @param philo_list 
/// @param print_lock blocks the threads at the start, blocks printing
/// @return 
static int	create_threads(t_philosopher *philo_list, sem_t *print_lock,
				struct timeval *main_start, sem_t *fork_lock)
{
	t_philosopher	*current;
	pid_t			pro_id;

	current = philo_list;
	while (current != NULL)
	{
		current->var_lock = sem_open(current->var_lock_name,
				O_CREAT | O_EXCL, 0644, 1);
		if (current->var_lock == SEM_FAILED)
			return (printf("sem open\n"), 1);
		current->print_lock = print_lock;
		current->main_start = main_start;
		current->fork_lock = fork_lock;
		pro_id = fork();
		if (pro_id == -1)
			return (printf("Fork fail\n"), 1);
		if (pro_id == 0)
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
		sem_wait(&current->var_lock);
		current->isdead = true;
		sem_post(&current->var_lock);
		current = current->next;
	}
	wait_ms(philo_list->philo_var.time_to_eat
		+ philo_list->philo_var.time_to_sleep + 10);
}

static void	join_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
}
