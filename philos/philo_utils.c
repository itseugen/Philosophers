/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:08:07 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/21 20:17:55 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief Checks if the philosopher should be dead
/// @param philo 
void	starving(t_philosopher *philo)
{
	long	time_since_last_meal;

	if (philo == NULL)
		return ;
	pthread_mutex_lock(&philo->var_lock);
	time_since_last_meal = get_ms(philo->start_time) - philo->last_meal;
	if (time_since_last_meal >= philo->philo_var.time_to_die)
	{
		pthread_mutex_unlock(&philo->var_lock);
		pthread_mutex_lock(philo->print_lock);
		printf("%ld %d died\n", get_ms(philo->start_time), philo->id);
		pthread_mutex_lock(&philo->var_lock);
		philo->isdead = true;
		pthread_mutex_unlock(&philo->var_lock);
	}
	else
		pthread_mutex_unlock(&philo->var_lock);
}

/// @brief makes the philo eat
/// @param philo 
void	eat(t_philosopher *philo)
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
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->var_lock);
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->var_lock);
	wait_ms(philo->philo_var.time_to_eat);
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->fork_left->fork_lock);
}

void	print_action(t_philosopher *philo, int content)
{
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_lock(&philo->var_lock);
	if (content == FORK && philo->isdead != true)
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
	else if (content == EAT && philo->isdead != true)
		printf("%ld %d is eating\n", get_ms(philo->start_time), philo->id);
	else if (content == SLEEP && philo->isdead != true)
		printf("%ld %d is sleeping\n", get_ms(philo->start_time), philo->id);
	else if (content == THINK && philo->isdead != true)
		printf("%ld %d is thinking\n", get_ms(philo->start_time), philo->id);
	pthread_mutex_unlock(&philo->var_lock);
	pthread_mutex_unlock(philo->print_lock);
}

bool	has_eaten_enough(t_philosopher *philo)
{
	t_philosopher	*current;

	current = philo;
	if (current->philo_var.num_has_to_eat == -2)
		return (false);
	while (current != NULL)
	{
		pthread_mutex_lock(&current->var_lock);
		if (current->num_eaten < current->philo_var.num_has_to_eat)
		{
			pthread_mutex_unlock(&current->var_lock);
			return (false);
		}
		pthread_mutex_unlock(&current->var_lock);
		current = current->next;
	}
	return (true);
}
