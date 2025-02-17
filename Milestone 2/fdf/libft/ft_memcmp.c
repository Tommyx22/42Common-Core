/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:28:51 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:20:09 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dest;
	const unsigned char	*src;
	size_t				i;

	i = 0;
	dest = (const unsigned char *)s1;
	src = (const unsigned char *)s2;
	while (i < n)
	{
		if (dest[i] != src[i])
		{
			return (dest[i] - src[i]);
		}
		i++;
	}
	return (0);
}
// int main() {
// 	char str1[] = "Hello";
// 	char str2[] = "Hello, World!";

// 	int result = ft_memcmp(str1, str2, 5);  // Confronta i primi 5 byte
// 	if (result == 0)
// 		printf("I primi 5 caratteri sono uguali.\n");
// 	else
// 		printf("I primi 5 caratteri sono diversi.\n");
// 	printf("%d\n", result);
// 	return 0;
// }