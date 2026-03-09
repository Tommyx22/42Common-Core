/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:27:45 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/09 16:34:44 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game, int floor_color)
{
	int	x;
	int	y;

	y = WINDOW_HEIGHT / 2;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray.hit = 0;
		cast_ray(game, &ray, x);
		draw_textured_column(game, x, &ray);
		x++;
	}
}

void	display_frame(t_game *game)
{
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img, 0, 0);
}
