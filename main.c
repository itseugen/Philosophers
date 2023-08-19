/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:13:45 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/19 14:52:48 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_var	philo_var;

	philo_var.num_has_to_eat = -2;
	if (get_input(argc, argv, &philo_var) == 1)
		return (0);
	printf("Num of philos: %d\n", philo_var.num_of_philo);
	printf("Time to die: %d\n", philo_var.time_to_die);
	printf("Time to eat: %d\n", philo_var.time_to_eat);
	printf("Time to sleep: %d\n", philo_var.time_to_sleep);
	printf("Num has to eat: %d\n", philo_var.num_has_to_eat);
	return (0);
}
