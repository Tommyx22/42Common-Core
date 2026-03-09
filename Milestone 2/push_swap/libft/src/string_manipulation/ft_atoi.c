/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:45:39 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	atoi;
	int		min;

	i = 0;
	atoi = 0;
	min = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			min = -min;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		atoi = ((atoi * 10) + (nptr[i] - 48));
		i++;
	}
	return (atoi * min);
}
