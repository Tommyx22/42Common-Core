/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:14:51 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*temp;

	temp = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	ft_strcpy(temp, s);
	return (temp);
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