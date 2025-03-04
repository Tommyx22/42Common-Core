/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:33:52 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countsize(unsigned long n, size_t len_base);
static void		ft_convbase(unsigned long nbr, char *num, char *base, size_t i);

char	*ft_uitoa_base(unsigned long nbr, char *base)
{
	size_t		len_nbr;
	size_t		len_base;
	char		*number;

	len_base = ft_strlen(base);
	len_nbr = ft_countsize(nbr, len_base);
	number = malloc((len_nbr + 1) * sizeof(char));
	if (!number)
		return (NULL);
	number[len_nbr--] = '\0';
	ft_convbase(nbr, number, base, len_nbr);
	return (number);
}

static size_t	ft_countsize(unsigned long n, size_t len_base)
{
	if ((n / len_base) == 0)
		return (1);
	else
		return (1 + ft_countsize(n / len_base, len_base));
}

static void	ft_convbase(unsigned long nbr, char *num, char *base, size_t i)
{
	size_t	len_base;

	len_base = ft_strlen(base);
	if (nbr >= (unsigned long int)len_base)
		ft_convbase((nbr / len_base), num, base, (i - 1));
	num[i] = base[nbr % len_base];
}
