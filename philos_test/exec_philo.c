/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:03 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/21 18:06:53 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	do_first_action(t_philosopher *philo);

//! Starving should print death

void	*philosopher(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(&philo->var_lock);
	philo->start_time = *(philo->main_start);
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten = 0;
	pthread_mutex_unlock(&philo->var_lock);
	do_first_action(philo);
	while (philo->isdead == false)
	{
		eat(philo);
		print_action(philo, SLEEP);
		wait_ms(philo->philo_var.time_to_sleep);
		print_action(philo, THINK);
	}
	return (0);
}

static void	do_first_action(t_philosopher *philo)
{
	print_action(philo, THINK);
	if (philo->id % 2 != 0)
	{
		eat(philo);
		print_action(philo, SLEEP);
		wait_ms(philo->philo_var.time_to_sleep);
	}
	else
	{
		print_action(philo, SLEEP);
		wait_ms(philo->philo_var.time_to_sleep);
	}
	print_action(philo, THINK);
}
