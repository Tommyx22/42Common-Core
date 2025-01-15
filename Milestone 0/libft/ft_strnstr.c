/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:13:39 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 15:23:21 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] != '\0' && i + j < len)
			{
				if (big[i + j] != little[j])
					break ;
				j++;
			}
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
// #include <stdio.h>
// int     main()
// {
// 	char    str[] = "oh no not the empty string !";
// 	char    find[] = "";
// 	printf("%s", ft_strnstr(str, find, 0));
// }