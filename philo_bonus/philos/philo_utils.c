/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:08:07 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 15:55:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	even_fork_lock(t_philosopher *philo);

/// @brief Checks if the philosopher should be dead
/// @param philo 
void	starving(t_philosopher *philo)
{
	long	time_since_last_meal;

	if (philo == NULL)
		return ;
	sem_wait(&philo->var_lock);
	time_since_last_meal = get_ms(philo->start_time) - philo->last_meal;
	if (time_since_last_meal >= philo->philo_var.time_to_die)
	{
		sem_post(&philo->var_lock);
		pthread_mutex_lock(philo->print_lock);
		printf("%ld %d died\n", get_ms(philo->start_time), philo->id);
		sem_wait(&philo->var_lock);
		philo->isdead = true;
		sem_post(&philo->var_lock);
	}
	else
		sem_post(&philo->var_lock);
}

/// @brief makes the philo eat
/// @param philo 
void	eat(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork_lock);
		print_action(philo, FORK);
		if (&(philo->fork_left->fork_lock) == &(philo->fork_lock))
		{
			wait_ms(philo->philo_var.time_to_die + 10);
			pthread_mutex_unlock(&philo->fork_lock);
			return ;
		}
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		print_action(philo, FORK);
	}
	else
		if (even_fork_lock(philo) == 1)
			return ;
	print_action(philo, EAT);
	sem_wait(&philo->var_lock);
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten++;
	sem_post(&philo->var_lock);
	wait_ms(philo->philo_var.time_to_eat);
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->fork_left->fork_lock);
}

static int	even_fork_lock(t_philosopher *philo)
{
	usleep(1000);
	pthread_mutex_lock(&philo->fork_left->fork_lock);
	print_action(philo, FORK);
	if (&(philo->fork_left->fork_lock) == &(philo->fork_lock))
	{
		wait_ms(philo->philo_var.time_to_die + 10);
		pthread_mutex_unlock(&philo->fork_lock);
		return (1);
	}
	pthread_mutex_lock(&philo->fork_lock);
	print_action(philo, FORK);
	return (0);
}

void	print_action(t_philosopher *philo, int content)
{
	sem_wait(philo->print_lock);
	sem_wait(&philo->var_lock);
	if (content == FORK && philo->isdead != true)
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
	else if (content == EAT && philo->isdead != true)
		printf("%ld %d is eating\n", get_ms(philo->start_time), philo->id);
	else if (content == SLEEP && philo->isdead != true)
		printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
	else if (content == THINK && philo->isdead != true)
		printf("%ld %d is thinking\n", get_ms(philo->start_time), philo->id);
	sem_post(&philo->var_lock);
	sem_post(philo->print_lock);
}

bool	has_eaten_enough(t_philosopher *philo)
{
	t_philosopher	*current;

	current = philo;
	if (current->philo_var.num_has_to_eat == -2)
		return (false);
	while (current != NULL)
	{
		sem_wait(&current->var_lock);
		if (current->num_eaten < current->philo_var.num_has_to_eat)
		{
			sem_post(&current->var_lock);
			return (false);
		}
		sem_post(&current->var_lock);
		current = current->next;
	}
	return (true);
}
