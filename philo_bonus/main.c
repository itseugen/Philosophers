/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:13:45 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/28 18:06:50 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_leaks(void)
{
	system("leaks philo_bonus");
}

int	main(int argc, char *argv[])
{
	t_philo_var		philo_var;
	t_philosopher	*philo_list;

	sem_unlink("/fork_lock");
	sem_unlink("/print_lock");
	sem_unlink("/fully_fed");
	sem_unlink("/set_dead");
	sem_unlink("/sim_end");
	// return (1);
	// atexit(check_leaks);
	philo_var.num_has_to_eat = -2;
	if (get_input(argc, argv, &philo_var) == 1)
		return (0);
	philo_list = init_philos(philo_var);
	if (philo_list == NULL)
		return (1);
	if (simulation(philo_list) == 1)
		return (free_philos(&philo_list), 1);
	free_philos(&philo_list);
	return (0);
}
