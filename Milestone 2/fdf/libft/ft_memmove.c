/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:19:34 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dst;
	const char	*str;

	if (!dest && !src)
		return (dest);
	i = 0;
	dst = dest;
	str = src;
	if (dest <= src)
	{
		while (n--)
		{
			dst[i] = str[i];
			i++;
		}
	}
	else
	{
		while (i + 1 <= n--)
			dst[n] = str[n];
	}
	return (dst);
}
// #include <stdio.h>
// int main() {
//     char buffer[20] = "Ciao mondo!!!!!!!!";
//     printf("Buffer: %s\n", (char *)ft_memmove(buffer + 2, buffer, 2));
//     return 0;
// }