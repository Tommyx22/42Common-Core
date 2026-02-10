/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/06 12:00:00 by tolanini         ###   ########.fr       */
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

int	take_color(char *line, t_color *color)
{
	char	**rgb;
	char	*trimmed;
	int		i;

	if (color->set)
		return (ft_putstr_fd("Error\nDouble initialization color\n", 2), 0);
	trimmed = skip_spaces(line);
	if (!trimmed || *trimmed == '\0')
		return (ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	rgb = ft_split(trimmed, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
		return (ft_free_split(rgb),
			ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	i = -1;
	while (rgb[++i])
	{
		if (!is_valid_int(rgb[i]))
			return (ft_free_split(rgb),
				ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (ft_putstr_fd("Error\nColor values must be 0-255\n", 2), 0);
	return (color->set = 1, 1);
}
