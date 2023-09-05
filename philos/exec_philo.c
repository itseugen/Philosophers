/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:54:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/05 17:09:58 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*one_philo(void *param)
{
	t_philosopher	*this_philo;

	this_philo = (t_philosopher *)param;
	printf("Id: %d\n", this_philo->id);
	return (0);
}

int	create_threads(t_philosopher *philo_list)
{
	t_philosopher	*current;

	current = philo_list;
	while (current != NULL)
	{
		if (pthread_create(&(current->thread), NULL, one_philo, current) != 0)
			return (perror("pthread creation"), 1);
		current = current->next;
	}
	while (current != NULL)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	return (0);
}
