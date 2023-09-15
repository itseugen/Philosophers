/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:20 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/15 19:10:47 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief Checks if the philosopher should be dead
/// @param philo 
void	starving(t_philosopher *philo)
{
	long	time_since_last_meal;

	time_since_last_meal = get_ms(philo->start_time) - philo->last_meal;
	if (time_since_last_meal >= philo->philo_var.time_to_die)
		philo->isdead = true;
}

/// @brief makes the philo eat
/// @param philo 
void	eat(t_philosopher *philo)
{
	philo->fork = LOCK;
	if (philo->fork_left->fork == LOCK)
	{
		philo->fork = FREE;
		return ;
	}
	philo->fork_left->fork = LOCK;
	pthread_mutex_lock(&philo->fork_lock);
	if (*(philo->print_lock) == false)
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
	pthread_mutex_lock(&philo->fork_left->fork_lock);
	if (*(philo->print_lock) == false)
		printf("%ld %d has taken a fork\n",
			get_ms(philo->start_time), philo->id);
	if (*(philo->print_lock) == false)
		printf("%ld %d is eating\n", get_ms(philo->start_time), philo->id);
	philo->last_meal = get_ms(philo->start_time);
	philo->num_eaten++;
	if (dies_during(philo, philo->philo_var.time_to_eat) == true)
		return ;
	wait_ms(philo->philo_var.time_to_eat);
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->fork_left->fork_lock);
	philo->fork = FREE;
	philo->fork_left->fork = FREE;
}

/// @brief Checks if the philo dies during his following action
/// @param philo 
/// @param action the time of the action about to be performed
/// @return returns true if he dies and falls if he does not
bool	dies_during(t_philosopher *philo, int action)
{
	if (get_ms(philo->start_time) - philo->last_meal + action
		> philo->philo_var.time_to_die)
	{
		wait_ms(philo->philo_var.time_to_die
			- (get_ms(philo->start_time) - philo->last_meal));
		philo->isdead = true;
		if (*(philo->print_lock) == false)
		{
			*(philo->print_lock) = true;
			printf("%ld %d died\n", get_ms(philo->start_time), philo->id);
		}
		return (true);
	}
	return (false);
}

void	print_action(t_philosopher *philo, int content)
{
	if (*(philo->print_lock) == false)
	{
		
	}
}
