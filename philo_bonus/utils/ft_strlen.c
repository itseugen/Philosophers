/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:03:05 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 15:05:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	str_len;

	str_len = 0;
	while (s[str_len] != '\0')
		str_len++;
	return (str_len);
}
