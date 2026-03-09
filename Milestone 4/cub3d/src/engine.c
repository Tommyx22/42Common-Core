/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:46 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/07 15:13:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	calculate_x_y(game, ray);
	perform_dda(game, ray);
	calculate_wall_dist(game, ray);
}

void	draw_textured_column(t_game *game, int x, t_ray *ray)
{
	t_draw_col	col;

	calculate_column_bounds(&col, ray->perp_wall_dist);
	select_texture(game, &col, ray);
	calculate_texture_x(game, &col, ray);
	setup_texture_sampling(&col);
	render_column_pixels(game, x, &col);
}

int	render_frame(t_game *game)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(&game->map.ceiling);
	floor_color = rgb_to_int(&game->map.floor);
	draw_ceiling(game, ceiling_color);
	draw_floor(game, floor_color);
	draw_walls(game);
	display_frame(game);
	return (0);
}
