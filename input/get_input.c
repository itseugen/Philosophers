/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:17:04 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/14 15:38:21 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	get_argv(char *str);
static bool	is_str_digit(char *str);

/// @brief Gets the input an writes it to a struct
/// @param argc 
/// @param argv 
/// @param philo_var the struct to write to
/// @return 0 if all went succesful or 1 if input was wrong
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

/// @brief Checks if string is a number and returns integer
/// @param str 
/// @return Returns the number got from str as an int
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

/// @brief Checks if the whole string is made of ints
/// @param str 
/// @return true if all chars a between 0 and 9
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
