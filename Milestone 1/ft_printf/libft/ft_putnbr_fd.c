/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:46:31 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 14:38:45 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../ft_printf.h"

int	ft_putnbr_fd(int n)
{
	int		temp;
	int		i;

	i = 0;
	if (n == 0)
		return (write(1, "0", 1), 1);
	else if (n < 0)
	{
		write (1, "-", ++i);
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return (i + 10);
		}
		n = -n;
	}
	temp = n;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	return (ft_conv(i, n, "0123456789"));
}
