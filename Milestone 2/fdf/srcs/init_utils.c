/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:59:41 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	**init_coordinates(int width, int depth)
{
	t_point	**coordinates;
	int		i;
	int		j;

	coordinates = ft_calloc(width, sizeof(t_point *));
	i = 0;
	while (i < width)
	{
		coordinates[i] = ft_calloc(depth, sizeof(t_point));
		if (!coordinates[i])
			return (NULL);
		j = 0;
		while (j < depth)
		{
			coordinates[i][j].x = 0;
			coordinates[i][j].y = 0;
			coordinates[i][j].z = 0;
			coordinates[i][j].color = 0;
			j++;
		}
		i++;
	}
	return (coordinates);
}

void	center_to_origin(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->max_y)
	{
		x = 0;
		while (x < map->max_x)
		{
			map->coordinates[x][y].x -= map->max_x / 2;
			map->coordinates[x][y].y -= map->max_y / 2;
			x++;
		}
		y++;
	}
}

float	scale_to_fit(t_map *map)
{
	float	scale_x;
	float	scale_y;
	float	scale_factor;

	scale_x = WINDOW_WIDTH / map->max_x;
	scale_y = WINDOW_HEIGHT / map->max_y;
	scale_factor = min(scale_x, scale_y);
	if (scale_factor < 4)
		return (2);
	return (scale_factor / 2);
}

void	reset(t_fdf *fdf)
{
	fdf->cam->scale_factor = scale_to_fit(fdf->map);
	fdf->cam->scale_z = 1;
	fdf->cam->move_x = WINDOW_WIDTH / 2;
	fdf->cam->move_y = WINDOW_HEIGHT / 2;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
}
