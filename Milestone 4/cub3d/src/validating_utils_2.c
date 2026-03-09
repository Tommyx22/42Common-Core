/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:14:52 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/09 15:56:30 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_rgb_split(char *trimmed)
{
	char	**rgb;

	rgb = ft_split(trimmed, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
	{
		ft_free_split(rgb);
		return (NULL);
	}
	return (rgb);
}

int	validate_rgb_values(char **rgb, t_color *color)
{
	int	i;

	i = -1;
	while (rgb[++i])
		if (!is_valid_int(rgb[i]))
			return (0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int	take_color(char *line, t_color *color)
{
	char	**rgb;
	char	*trimmed;

	if (color->set)
		return (ft_putstr_fd("Error\nDouble initialization color\n", 2), 0);
	trimmed = skip_spaces(line);
	if (!trimmed || *trimmed == '\0')
		return (ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	rgb = parse_rgb_split(trimmed);
	if (!rgb)
		return (ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	if (!validate_rgb_values(rgb, color))
	{
		ft_free_split(rgb);
		return (ft_putstr_fd("Error\nColor: invalid parameter\n", 2), 0);
	}
	ft_free_split(rgb);
	return (color->set = 1, 1);
}
