/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:31:45 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:21:50 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	length;

	length = ft_strlen(s);
	str = (char *)malloc(length + 1);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s);
	return (str);
}
// #include <stdio.h>
// int main()
// {
// 	const char s[] = "Origine";
// 	char *copy = ft_strdup(s);

// 	printf("Stringa originale: %s\n", s);
// 	printf("Stringa copiata: %s\n", copy);
//     free(copy);
// }