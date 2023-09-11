/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:35:03 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/11 16:28:54 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

struct timeval	get_start_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time);
}

long	get_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long			comb_s;
	long			comb_mis;
	long			ms_since_start;

	gettimeofday(&current_time, NULL);
	comb_s = (current_time.tv_sec - start_time.tv_sec) * 1000;
	comb_mis = (current_time.tv_usec - start_time.tv_usec) / 1000;
	ms_since_start = comb_s + comb_mis;
	return (ms_since_start);
}

/// @brief Waits ms milliseconds
/// @param ms the amount of ms to wait
/// @param start_time the simulation starttume
void	wait_ms(long ms)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (get_ms(start_time) < ms)
		usleep(100);
}
