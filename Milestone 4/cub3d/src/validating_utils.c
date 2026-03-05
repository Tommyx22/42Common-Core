/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/10 15:38:21 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (ERROR);
}

char	*skip_spaces(char *s)
{
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	free_map(t_map *map)
{
	if (map->grid)
		ft_free_split(map->grid);
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
}

int	rgb_to_int(t_color *color)
{
	return ((color->r << 16) | (color->g << 8) | color->b);
}
