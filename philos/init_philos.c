/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:05:28 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/05 16:25:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int				add_philo(t_philosopher **philo_list, int id);
static t_philosopher	*get_last_philo(t_philosopher **philo_list);

t_philosopher	*init_philo(t_philo_var philo_var)
{
	int				i;
	t_philosopher	*philo_list;

	philo_list = malloc(sizeof(t_philosopher));
	if (philo_list == NULL)
		return (perror("malloc fail"), NULL);
	philo_list->next = NULL;
	philo_list->id = 1;
	i = 0;
	while (i < philo_var.num_of_philo - 1)
	{
		if (add_philo(&philo_list, i + 2) == -1)
			return (free_philos(&philo_list), NULL);
		i++;
	}
	philo_list->fork_left = get_last_philo(&philo_list);
	return (philo_list);
}

static t_philosopher	*get_last_philo(t_philosopher **philo_list)
{
	t_philosopher	*current;

	current = *philo_list;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

static int	add_philo(t_philosopher **philo_list, int id)
{
	t_philosopher	*new_philo;
	t_philosopher	*last_philo;

	last_philo = get_last_philo(philo_list);
	new_philo = malloc(sizeof(t_philosopher));
	if (new_philo == NULL)
		return (-1);
	new_philo->id = id;
	last_philo->next = new_philo;
	new_philo->fork_left = last_philo;
	return (0);
}

void	free_philos(t_philosopher **philo_list)
{
	t_philosopher	*current;
	t_philosopher	*free_me;

	current = *philo_list;
	current = current->next;
	free_me = *philo_list;
	free(free_me);
	while (current != NULL)
	{
		free_me = current;
		current = current->next;
		free(free_me);
	}
	*philo_list = NULL;
}
