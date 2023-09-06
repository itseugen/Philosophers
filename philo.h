/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:12 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/06 15:02:48 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                Libraries                                   */
/* ************************************************************************** */

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/* ************************************************************************** */
/*                                Defines                                     */
/* ************************************************************************** */

# define FREE 0
# define LOCK 1

/* ************************************************************************** */
/*                                Typedefs                                    */
/* ************************************************************************** */

typedef struct s_philo_var
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_has_to_eat;
}	t_philo_var;

typedef struct s_philosopher
{
	pthread_t				thread;
	int						id;
	int						fork;
	struct s_philosopher	*fork_left;
	struct s_philosopher	*next;
	pthread_mutex_t			fork_lock;
	t_philo_var				philo_var;
}	t_philosopher;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int				get_input(int argc, char *argv[], t_philo_var *philo_var);
void			free_philos(t_philosopher **philo_list);
t_philosopher	*init_philo(t_philo_var philo_var);
int				create_threads(t_philosopher *philo_list);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

long int	ft_atoi_long(const char *str);
size_t		ft_strlen(const char *s);

#endif