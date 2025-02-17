/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:49:16 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:22:58 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
// #include <stdio.h>
// char ft_mytoupper(unsigned int i, char c)
// {
//     (void)i;
//     if (c >= 'a' && c <= 'z')
//     {
//         return c - 'a' + 'A';
//     }
//     return c;
// }
// int main()
// {
// 	char str[] = "ciao";
// 	printf("%s", ft_strmapi(str, ft_mytoupper));
// }