/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:47:03 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/28 19:06:17 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	do_first_action(t_philosopher *philo);
void		*set_philo_dead(void *param);

void	*philosopher(void *param)
{
	t_philosopher	*philo;
	pthread_t		thread;
	pthread_t		thread2;
	struct timeval	c_time;

	philo = (t_philosopher *)param;
	sem_wait(philo->print_lock);
	gettimeofday(&c_time, NULL);
	while(c_time.tv_sec < philo->main_start->tv_sec
		|| (c_time.tv_sec == philo->main_start->tv_sec
		&& c_time.tv_usec < philo->main_start->tv_usec))
	{
		usleep(60);
		gettimeofday(&c_time, NULL);
	}
	sem_post(philo->print_lock);
	sem_wait(philo->var_lock);
	philo->start_time = *philo->main_start;
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten = 0;
	if (pthread_create(&thread, NULL, monitor_thread, philo) != 0)
		sem_post(philo->sim_end);
	if (pthread_create(&thread2, NULL, set_philo_dead, philo) != 0)
		sem_post(philo->sim_end);
	sem_post(philo->var_lock);
	do_first_action(philo);
	sem_wait(philo->var_lock);
	while (philo->isdead == false)
	{
		sem_post(philo->var_lock);
		eat(philo);
		print_action(philo, SLEEP);
		wait_ms(philo->philo_var.time_to_sleep);
		print_action(philo, THINK);
		sem_wait(philo->var_lock);
	}
	sem_post(philo->var_lock);
	pthread_detach(thread);
	pthread_detach(thread2);
	exit(0);
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

void	*monitor_thread(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	sem_wait(philo->print_lock);
	sem_post(philo->print_lock);
	wait_ms(philo->philo_var.time_to_die);
	while (1)
	{
		starving(philo);
		sem_wait(philo->var_lock);
		if (philo->isdead == true)
		{
			sem_post(philo->var_lock);
			break ;
		}
		sem_post(philo->var_lock);
	}
	return (0);
}

void	*set_philo_dead(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	sem_wait(philo->sim_end);
	sem_post(philo->sim_end);
	sem_wait(philo->var_lock);
	philo->isdead = true;
	sem_post(philo->var_lock);
	return (0);
}
