/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/12 14:09:17 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	do_first(t_philosopher *philo);

static void	*one_philo(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	philo->start_time = get_start_time();
	do_first(philo);
	while (philo->isdead == false)
	{
		if (philo->fork == FREE && philo->fork_left->fork == FREE)
		{
			philo->fork = LOCK;
			philo->fork_left->fork = LOCK;
			pthread_mutex_lock(&philo->fork_lock);
			printf("%ld %d has taken a fork\n",
				get_ms(philo->start_time), philo->id);
			pthread_mutex_lock(&philo->fork_left->fork_lock);
			printf("%ld %d has taken a fork\n",
				get_ms(philo->start_time), philo->id);
			printf("%ld %d is eating\n", get_ms(philo->start_time), philo->id);
			philo->num_eaten++;
			// if (philo->num_eaten == philo->philo_var.num_has_to_eat)
			// 	setsomevartoindicatefinishing();
			wait_ms(philo->philo_var.time_to_eat);
			pthread_mutex_unlock(&philo->fork_lock);
			pthread_mutex_unlock(&philo->fork_left->fork_lock);
			philo->fork = FREE;
			philo->fork_left->fork = FREE;
			printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
			wait_ms(philo->philo_var.time_to_sleep);
			printf("%ld %d is thinking\n", get_ms(philo->start_time), philo->id);
		}
	}
	printf("%d has eaten: %d times\n", philo->id, philo->num_eaten);
	printf("ID: %d Current time since start: %ldms\n", philo->id, get_ms(philo->start_time));
	return (0);
}

static void	do_first(t_philosopher *philo)
{
	if (philo->fork == FREE && philo->fork_left->fork == FREE)
	{
		philo->fork = LOCK;
		philo->fork_left->fork = LOCK;
		pthread_mutex_lock(&philo->fork_lock);
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
		printf("%ld %d is eating\n", get_ms(philo->start_time), philo->id);
		wait_ms(philo->philo_var.time_to_eat);
		pthread_mutex_unlock(&philo->fork_lock);
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		philo->fork = FREE;
		philo->fork_left->fork = FREE;
		printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
		wait_ms(philo->philo_var.time_to_sleep);
	}
	else
	{
		printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
		wait_ms(philo->philo_var.time_to_sleep);
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
	while (current != NULL)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}

	return (0);
}
