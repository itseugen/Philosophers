/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/20 19:43:12 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	do_first(t_philosopher *philo);

//! Idea: Make thread or let mainthread check if philo is dead while thinking

/// @brief The function each philo uses
/// @param param 
/// @return 
static void	*one_philo(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	// philo->start_time = get_start_time();
	philo->start_time = *(philo->main_start);
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten = 0;
	do_first(philo);
	while (philo->isdead == false)
	{
		eat(philo);
		print_action(philo, SLEEP);
		wait_ms(philo->philo_var.time_to_sleep);
		print_action(philo, THINK);
	}
	return (0);
}

static void	do_first(t_philosopher *philo)
{
	print_action(philo, THINK);
	if (philo->id % 2 != 0)
	{
		eat(philo);
		if (philo->isdead == false)
		{
			print_action(philo, SLEEP);
			wait_ms(philo->philo_var.time_to_sleep);
		}
	}
	else
	{
		if (philo->isdead == false)
		{
			print_action(philo, SLEEP);
			wait_ms(philo->philo_var.time_to_sleep);
		}
	}
	print_action(philo, THINK);
}

/// @brief Creates the threads and controlls them after (might be changed)
/// @param philo_list 
/// @return 
//! If weird segfaults occure, make sure to make current = philo list
//!before freeing the forks
int	create_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;
	pthread_mutex_t	print_lock;
	struct timeval	main_start;

	if (pthread_mutex_init(&print_lock, NULL) != 0)
		return (printf("mutex creation\n"), 1);
	current = philo_list;
	pthread_mutex_lock(&print_lock);
	while (current != NULL)
	{
		if (pthread_mutex_init(&(current->fork_lock), NULL) != 0)
			return (printf("mutex creation\n"), 1);
		if (pthread_create(&(current->thread), NULL, one_philo, current) != 0)
			return (printf("pthread creation\n"), 1);
		current->print_lock = &print_lock;
		current->main_start = &main_start;
		current = current->next;
	}
	main_start = get_start_time();
	pthread_mutex_unlock(&print_lock);
	monitor_threads(philo_list);
	current = philo_list;
	while (current != NULL)
	{
		current->isdead = true;
		pthread_mutex_unlock(&current->fork_lock);
		pthread_mutex_unlock(&current->fork_left->fork_lock);
		// pthread_join(current->thread, NULL);
		pthread_detach(current->thread);
		current = current->next;
	}
	// pthread_mutex_unlock(current->print_lock);
	pthread_mutex_destroy(&print_lock);
	return (0);
}

/// @brief Checks if the philos should stop
/// @param philo_list 
void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	// usleep(1000);
	wait_ms(current->philo_var.time_to_die - 10);
	while (1)
	{
		starving(current);
		if (current->isdead == true)
		{
			print_action(current, DIE);
			break ;
		}
		current = current->next;
		if (has_eaten_enough(philo_list) == true)
			break ;
		if (current == NULL)
			current = philo_list;
		// usleep(100);
	}
}
