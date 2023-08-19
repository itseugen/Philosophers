/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:17:04 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/19 14:53:00 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	get_argv(char *str);
static bool	is_str_digit(char *str);

int	get_input(int argc, char *argv[], t_philo_var *philo_var)
{
	if (argc < 5 || argc > 6)
		return (1);
	philo_var->num_of_philo = get_argv(argv[1]);
	philo_var->time_to_die = get_argv(argv[2]);
	philo_var->time_to_eat = get_argv(argv[3]);
	philo_var->time_to_sleep = get_argv(argv[4]);
	if (argc == 6)
		philo_var->num_has_to_eat = get_argv(argv[5]);
	if (philo_var->num_of_philo == -1 || philo_var->time_to_die == -1
		|| philo_var->time_to_eat == -1 || philo_var->time_to_sleep == -1
		|| philo_var->num_has_to_eat == -1)
		return (1);
	return (0);
}

static int	get_argv(char *str)
{
	long int	num;

	if (is_str_digit(str) == false)
		return (-1);
	if (ft_strlen(str) > 10)
		return (-1);
	num = ft_atoi_long(str);
	if (num > 2147483647 || num < 0)
		return (-1);
	return ((int)num);
}

static bool	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
