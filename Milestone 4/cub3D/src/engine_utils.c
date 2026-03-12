/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:08:29 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:19:52 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_column_bounds(t_draw_col *col, double perp_wall_dist)
{
	col->line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	col->draw_start = -col->line_height / 2 + WINDOW_HEIGHT / 2;
	if (col->draw_start < 0)
		col->draw_start = 0;
	col->draw_end = col->line_height / 2 + WINDOW_HEIGHT / 2;
	if (col->draw_end >= WINDOW_HEIGHT)
		col->draw_end = WINDOW_HEIGHT - 1;
}

void	select_texture(t_game *game, t_draw_col *col, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			col->tex = &game->tex_east;
		else
			col->tex = &game->tex_west;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			col->tex = &game->tex_south;
		else
			col->tex = &game->tex_north;
	}
}

void	calculate_texture_x(t_game *game, t_draw_col *col, t_ray *ray)
{
	if (ray->side == 0)
		col->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		col->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	col->wall_x -= floor(col->wall_x);
	col->tex_x = (int)(col->wall_x * (double)col->tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		col->tex_x = col->tex->width - col->tex_x - 1;
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= col->tex->width)
		col->tex_x = col->tex->width - 1;
}

void	setup_texture_sampling(t_draw_col *col)
{
	col->step = 1.0 * col->tex->height / col->line_height;
	col->tex_pos = (col->draw_start - WINDOW_HEIGHT / 2 + col->line_height / 2)
		* col->step;
	col->y = col->draw_start;
}

void	render_column_pixels(t_game *game, int x, t_draw_col *col)
{
	while (col->y < col->draw_end)
	{
		col->tex_y = (int)col->tex_pos & (col->tex->height - 1);
		col->tex_pos += col->step;
		if (col->tex_y < 0)
			col->tex_y = 0;
		if (col->tex_y >= col->tex->height)
			col->tex_y = col->tex->height - 1;
		col->color = get_texture_color(col->tex, col->tex_x, col->tex_y);
		my_mlx_pixel_put(game, x, col->y, col->color);
		col->y++;
	}
}
