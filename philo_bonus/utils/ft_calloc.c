/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:50 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/26 14:34:52 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	ft_bzero(void *str, size_t n);

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && (count * size) / count != size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

static void	ft_bzero(void *str, size_t n)
{
	unsigned int	i;
	char			*str2;

	str2 = (char *)str;
	i = 0;
	while (i < n)
	{
		str2[i] = 0;
		i++;
	}
}
