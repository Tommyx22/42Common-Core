/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:43:29 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:15:41 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*str;
	char		*cpy;

	i = 0;
	str = src;
	cpy = dest;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		cpy[i] = str[i];
		i++;
	}
	return (cpy);
}
// #include <stdio.h>
// int main(void)
// {
// 	char source[] = "This is the source string";
// 	char target[] = "cringe";
// 	printf( "%s\n", (char *)ft_memcpy( target, source, 12));
// }