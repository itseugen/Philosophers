/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/18 19:22:50 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	do_first(t_philosopher *philo);
static bool	has_eaten_enough(t_philosopher *philo);

//! Idea: Make thread or let mainthread check if philo is dead while thinking

/// @brief The function each philo uses
/// @param param 
/// @return 
static void	*one_philo(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	philo->start_time = get_start_time();
	philo->last_meal = 0;
	philo->num_eaten = 0;
	do_first(philo);
	while (philo->isdead == false)
	{
		if (philo->fork == FREE && philo->fork_left->fork == FREE)
		{
			eat(philo);
			print_action(philo, SLEEP);
			if (dies_during(philo, philo->philo_var.time_to_sleep) == true)
				break ;
			wait_ms(philo->philo_var.time_to_sleep);
			print_action(philo, THINK);
			// usleep(100);
		}
		// else
		// {
		// 	starving(philo);
		// 	if (philo->isdead == true)
		// 		print_action(philo, DIE);
		// }
	}
	return (0);
}

static void	do_first(t_philosopher *philo)
{
	if (philo->id % 2 != 0 && philo->fork == FREE
		&& philo->fork_left->fork == FREE)
	{
		eat(philo);
		if (philo->isdead == false
			&& dies_during(philo, philo->philo_var.time_to_sleep) == false)
		{
			print_action(philo, SLEEP);
			wait_ms(philo->philo_var.time_to_sleep);
		}
	}
	else
	{
		if (philo->isdead == false
			&& dies_during(philo, philo->philo_var.time_to_sleep) == false)
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
int	create_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;
	bool			print_lock;

	print_lock = false;
	current = philo_list;
	while (current != NULL)
	{
		if (pthread_mutex_init(&(current->fork_lock), NULL) != 0)
			return (printf("mutex creation\n"), 1);
		if (pthread_create(&(current->thread), NULL, one_philo, current) != 0)
			return (printf("pthread creation\n"), 1);
		current->print_lock = &print_lock;
		current = current->next;
	}
	monitor_threads(philo_list);
	current = philo_list;
	while (current != NULL)
	{
		current->isdead = true;
		pthread_detach(current->thread);
		current = current->next;
	}
	return (0);
}

/// @brief Checks if the philos should stop
/// @param philo_list 
void	monitor_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	while (1)
	{
		starving(current);
		if (current->isdead == true)
		{
			if (*(current->print_lock) == false)
				print_action(current, DIE);
			break ;
		}
		current = current->next;
		if (has_eaten_enough(philo_list) == true)
			break ;
		if (current == NULL)
			current = philo_list;
		usleep(100);
	}
}

/// @brief Checks if all philos have eaten num_has_eaten times
/// @param philo 
/// @return true if all philos have eaten
static bool	has_eaten_enough(t_philosopher *philo)
{
	t_philosopher	*current;

	current = philo;
	if (current->philo_var.num_has_to_eat == -2)
		return (false);
	while (current != NULL)
	{
		if (current->num_eaten < current->philo_var.num_has_to_eat)
			return (false);
		current = current->next;
	}
	return (true);
}
