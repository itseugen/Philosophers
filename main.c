/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:13:45 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/14 14:52:42 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	check_leaks(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char *argv[])
{
	t_philo_var		philo_var;
	t_philosopher	*philo_list;

	// atexit(check_leaks);
	philo_var.num_has_to_eat = -2;
	if (get_input(argc, argv, &philo_var) == 1)
		return (0);
	// printf("Num of philos: %d\n", philo_var.num_of_philo);
	// printf("Time to die: %d\n", philo_var.time_to_die);
	// printf("Time to eat: %d\n", philo_var.time_to_eat);
	// printf("Time to sleep: %d\n", philo_var.time_to_sleep);
	// printf("Num has to eat: %d\n", philo_var.num_has_to_eat);
	philo_list = init_philo(philo_var);
	if (philo_list == NULL)
		return (1);
	// while (philo_list->next != NULL)
	// {
	// 	printf("Philo ID: %d\n", philo_list->id);
	// 	philo_list = philo_list->next;
	// }
	// printf("Philo ID: %d\n", philo_list->id);
	if (create_threads(philo_list) == 1)
		return (free_philos(&philo_list), 1);
	free_philos(&philo_list);
	return (0);
}
