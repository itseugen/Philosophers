/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/08 14:30:15 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*one_philo(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	philo->start_time = get_start_time();
	// printf("Time to eat: %d\n", philo->philo_var.time_to_eat);
	if (philo->fork == FREE && philo->fork_left->fork == FREE)
	{
		philo->fork = LOCK;
		philo->fork_left->fork = LOCK;
		pthread_mutex_lock(&philo->fork_lock);
		printf("ID: %d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		printf("ID: %d has taken a fork\n", philo->id);
		printf("ID: %d is eating\n", philo->id);
		sleep(3);
		pthread_mutex_unlock(&philo->fork_lock);
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		printf("ID: %d is sleeping\n", philo->id);
		sleep(4);
	}
	else
	{
		printf("ID: %d is sleeping\n", philo->id);
		sleep(4);
	}
	usleep(10000);
	printf("ID: %d is thinking\n", philo->id);
	printf("ID: %d Current time since start: %ldms\n", philo->id, get_ms(philo->start_time));

	return (0);
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
