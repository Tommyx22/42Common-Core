/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:58:31 by tolanini          #+#    #+#             */
/*   Updated: 2024/11/25 19:20:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_wrld(char const *s, char c)
{
	int		wrld;
	size_t	i;

	wrld = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wrld++;
		i++;
	}
	return (wrld);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;

	ptr = (char *) malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, n + 1);
	return (ptr);
}

static char	**ft_remove(char **tab, int wrld)
{
	while (wrld > 0)
		free(tab[wrld--]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		wrld;
	int		start;
	int		end;

	tab = (char **)malloc(sizeof(char *) * (ft_count_wrld(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	wrld = 0;
	start = 0;
	end = 0;
	while (wrld < ft_count_wrld(s, c))
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != c && s[end] != '\0')
			end++;
		tab[wrld] = ft_strndup(&s[start], end - start);
		if (!tab[wrld])
			return (ft_remove(tab, wrld));
		wrld++;
	}
	tab[wrld] = NULL;
	return (tab);
}
