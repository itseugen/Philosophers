/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:12 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/28 19:37:22 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>

/* ************************************************************************** */
/*                            Defines & enums                                 */
/* ************************************************************************** */

# define FREE 0
# define LOCK 1
# define C O_CREAT
# define E O_EXCL

enum e_print
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

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
	int						id;
	struct s_philosopher	*next;
	t_philo_var				philo_var;
	struct timeval			start_time;
	struct timeval			*main_start;
	bool					isdead;
	int						num_eaten;
	long					last_meal;
	sem_t					*print_lock;
	sem_t					*var_lock;
	char					*var_lock_name;
	sem_t					*fork_lock;
	sem_t					*sim_end;
	sem_t					*fully_fed;
	pid_t					pro_id;
}	t_philosopher;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int				get_input(int argc, char *argv[], t_philo_var *philo_var);
void			free_philos(t_philosopher **philo_list);
void			wait_ms(long ms);
long			get_ms(struct timeval start_time);
void			*philosopher(void *param);
int				simulation(t_philosopher *philo_list);
t_philosopher	*init_philos(t_philo_var philo_var);
void			*monitor_thread(void *param);

/* ************************************************************************** */
/*                                Philo Utils                                 */
/* ************************************************************************** */

void			starving(t_philosopher *philo);
void			eat(t_philosopher *philo);
bool			dies_during(t_philosopher *philo, int action);
void			print_action(t_philosopher *philo, int content);
bool			has_eaten_enough(t_philosopher *philo);
void			*set_philo_dead(void *param);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

long int		ft_atoi_long(const char *str);
size_t			ft_strlen(const char *s);
struct timeval	get_start_time(void);
void			*ft_calloc(size_t count, size_t size);
char			*ft_itoa(int n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
#endif