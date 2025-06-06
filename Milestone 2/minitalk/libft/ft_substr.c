/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:05:39 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:41 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}
// #include <stdio.h>
// int main()
// {
//     char sorgente[] = "Ciao, Mondo!";
//     printf("%s\n", ft_substr(sorgente, 6, 3));
//     return 0;
// }