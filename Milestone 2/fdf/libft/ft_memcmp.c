/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:19:16 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s11;
	const unsigned char	*s21;
	size_t				i;

	s11 = s1;
	s21 = s2;
	i = 0;
	while (i < n)
	{
		if (s11[i] != s21[i])
			return (s11[i] - s21[i]);
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