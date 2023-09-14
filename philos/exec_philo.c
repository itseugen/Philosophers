/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/14 13:45:46 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	do_first(t_philosopher *philo);
static bool	has_eaten_enough(t_philosopher *philo);

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
			if (philo->isdead == true)
				break ;
			printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
			if (dies_during(philo, philo->philo_var.time_to_sleep) == true)
				break ;
			wait_ms(philo->philo_var.time_to_sleep);
			printf("%ld %d is thinking\n", get_ms(philo->start_time), philo->id);
		}
		else
		{
			starving(philo);
			usleep(100);
			if (philo->isdead == true)
				printf("%ld %d died\n", get_ms(philo->start_time), philo->id);
		}
	}
	// printf("%d has eaten: %d times\n", philo->id, philo->num_eaten);
	// printf("ID: %d Current time since start: %ldms\n", philo->id, get_ms(philo->start_time));
	return (0);
}

//! Make depending on even id 
static void	do_first(t_philosopher *philo)
{
	if (philo->id % 2 != 0 && philo->fork == FREE && philo->fork_left->fork == FREE)
	{
		eat(philo);
		if (philo->isdead == false && dies_during(philo, philo->philo_var.time_to_sleep) == false)
		{
			printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
			wait_ms(philo->philo_var.time_to_sleep);
		}
	}
	else
	{
		if (philo->isdead == false && dies_during(philo, philo->philo_var.time_to_sleep) == false)
		{
			printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
			wait_ms(philo->philo_var.time_to_sleep);
		}
	}
	printf("%ld %d is thinking\n", get_ms(philo->start_time), philo->id);
}

int	create_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		if (pthread_mutex_init(&(current->fork_lock), NULL) != 0)
			return (printf("mutex creation\n"), 1);
		if (pthread_create(&(current->thread), NULL, one_philo, current) != 0)
			return (printf("pthread creation\n"), 1);
		current = current->next;
	}
	current = philo_list;
	while (1)
	{
		if (current->isdead == true)
			break ;
		current = current->next;
		if (has_eaten_enough(philo_list) == true)
			break ;
		if (current == NULL)
			current = philo_list;
		usleep(100);
	}
	current = philo_list;
	//! Add a bool print to indicate if the thread should print anything (or a mutex)
	while (current != NULL)
	{
		current->isdead = true;
		pthread_detach(current->thread);
		current = current->next;
	}
	return (0);
}

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
