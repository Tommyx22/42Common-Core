/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:45:39 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:41 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	atoi;
	int	min;

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
// #include <stdlib.h>
// #include <stdio.h>
// int	main()
// {
// 	char nptr[] = "42"; //-1 92233720368547750011
// 	printf("%d\n", atoi(nptr));
// 	printf("%d\n", ft_atoi(nptr));
// }