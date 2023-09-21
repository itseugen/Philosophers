/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:11 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/21 18:24:30 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	create_threads(t_philosopher *philo_list,
				pthread_mutex_t *print_lock, struct timeval main_start);

/// @brief Handles the simulation of the philos
/// @param philo_list 
/// @return 
int	simulation(t_philosopher *philo_list)
{
	pthread_mutex_t	print_lock;
	struct timeval	main_start;

	if (pthread_mutex_init(&print_lock, NULL) != 0)
		return (printf("mutex creation\n"), 1);
	pthread_mutex_lock(&print_lock);
	if (create_threads(philo_list, &print_lock) != 0)
		return (1);
	main_start = get_start_time();
	//* Starting the threads
	pthread_mutex_unlock(&print_lock);
}

/// @brief Checks if a philo has dies or all have eaten enough
/// @param philo_list 
static void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	wait_ms(current->philo_var.time_to_die - 15);
	while (1)
	{
		starving(current);
		pthread_mutex_lock(&current->var_lock);
		if (current->isdead == true)
		{
			pthread_mutex_unlock(&current->var_lock);
			break ;
		}
		pthread_mutex_unlock(&current->var_lock);
		if (has_eaten_enough(philo_list) == true)
			break ;
		current = current->next;
		if (current == NULL)
			current = philo_list;
	}
}

/// @brief IStarts the threads
/// @param philo_list 
/// @param print_lock blocks the threads at the start, blocks printing
/// @return 
static int	create_threads(t_philosopher *philo_list,
					pthread_mutex_t *print_lock, struct timeval main_start)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		if (pthread_mutex_init(&(current->fork_lock), NULL) != 0)
			return (printf("mutex creation\n"), 1);
		if (pthread_mutex_init(&(current->var_lock), NULL) != 0)
			return (printf("mutex creation\n"), 1);
		current->print_lock = print_lock;
		current->main_start = &main_start;
		if (pthread_create(&(current->thread), NULL, philosopher, current) != 0)
			return (printf("pthread creation\n"), 1);
		current = current->next;
	}
}
