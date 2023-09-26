/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:42:28 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 15:14:03 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int				add_philo(t_philosopher **philo_list,
							int id, t_philo_var philo_var);
static t_philosopher	*get_last_philo(t_philosopher **philo_list);
static char				*get_sem_name(int id);

t_philosopher	*init_philos(t_philo_var philo_var)
{
	int				i;
	t_philosopher	*philo_list;

	philo_list = ft_calloc(1, sizeof(t_philosopher));
	if (philo_list == NULL)
		return (perror("malloc fail"), NULL);
	philo_list->next = NULL;
	philo_list->id = 1;
	philo_list->philo_var = philo_var;
	philo_list->var_lock_name = get_sem_name(philo_list->id);
	if (philo_list->var_lock_name == NULL)
		return (free(philo_list), NULL);
	i = 0;
	while (i < philo_var.num_of_philo - 1)
	{
		if (add_philo(&philo_list, i + 2, philo_var) == -1)
			return (free_philos(&philo_list), NULL);
		i++;
	}
	return (philo_list);
}

/// @brief Returns a pointer to the last philo of the list
/// @param philo_list 
/// @return 
static t_philosopher	*get_last_philo(t_philosopher **philo_list)
{
	t_philosopher	*current;

	current = *philo_list;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

/// @brief adds and allocates a new philo
/// @param philo_list The list of the philos (to get prev)
/// @param id The id of the philo being added
/// @param philo_var THe varibles to store
/// @return 
static int	add_philo(t_philosopher **philo_list, int id, t_philo_var philo_var)
{
	t_philosopher	*new_philo;
	t_philosopher	*last_philo;

	last_philo = get_last_philo(philo_list);
	new_philo = ft_calloc(1, sizeof(t_philosopher));
	if (new_philo == NULL)
		return (-1);
	new_philo->id = id;
	last_philo->next = new_philo;
	new_philo->philo_var = philo_var;
	new_philo->var_lock_name = get_sem_name(new_philo->id);
	if (new_philo->var_lock == NULL)
		return (-1);
	return (0);
}

/// @brief Frees all philosophers
/// @param philo_list 
void	free_philos(t_philosopher **philo_list)
{
	t_philosopher	*current;
	t_philosopher	*free_me;

	current = *philo_list;
	current = current->next;
	free_me = *philo_list;
	sem_unlink(free_me->var_lock_name);
	free(free_me->var_lock_name);
	free(free_me);
	while (current != NULL)
	{
		free_me = current;
		current = current->next;
		sem_unlink(free_me->var_lock_name);
		free(free_me->var_lock_name);
		free(free_me);
	}
	*philo_list = NULL;
}

static char	*get_sem_name(int id)
{
	char	*id_str;
	char	*sem_name;

	id_str = ft_itoa(id);
	if (id_str == NULL)
		return (NULL);
	sem_name = ft_strjoin("/sem_", id_str);
	free(id);
	return (sem_name);
}
