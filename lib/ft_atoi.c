/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:54:24 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 13:54:38 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				s;

	s = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13
			&& str[i] != '\0') || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if ((res > 2147483647 && s == 1) || (res > 2147483648 && s == -1))
			return (2147483648);
		i++;
	}
	return (res * s);
}