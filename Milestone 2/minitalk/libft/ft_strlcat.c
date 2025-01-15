/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:15:35 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:22:22 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	res = 0;
	while (dst[i])
		i++;
	while (src[res])
		res++;
	if (size <= i)
		res += size;
	else
		res += i;
	while (src[j] && (i + 1) < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (res);
}
// #include <stdio.h>
// #include <bsd/string.h>
// int main() {
//     char dst[20] = "Ciao, ";
//     const char *src = "come va?";
// 	char dst1[20] = "Ciao, ";
//     const char *src1 = "come va?";
//     printf("%ld\n", ft_strlcat(dst, src, 15));
//     printf("%s\n", dst);
// 	printf("%ld\n", strlcat(dst1, src1, 15));
//     printf("%s\n", dst1);
// }