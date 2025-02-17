/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:22:31 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:22:52 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (!size)
		return (j);
	while ((src[i]) && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
// #include <stdio.h>
// #include <bsd/string.h>
// int main()
// {
//     char src[] = "Hello, world!";
//     char dst[10]; // Buffer di dstinazione di dimensione 10
//     size_t len = ft_strlcpy(dst, src, sizeof(dst));
//     printf("Dst: %s\n", dst);
//     printf("Length: %zu\n", len);
//     return 0;
// }