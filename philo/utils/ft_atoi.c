/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:37 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/19 14:24:12 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atoi_long(const char *str)
{
	int			is_n;
	int			i;
	long int	nbr;

	i = 0;
	is_n = 1;
	nbr = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (str[i] - 48);
		i++;
	}
	return (nbr * is_n);
}
