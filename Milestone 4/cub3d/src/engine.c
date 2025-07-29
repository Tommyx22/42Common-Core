/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:46 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/29 18:29:55 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void cast_ray(t_game *game, t_ray *ray, int x)
{
    (void)x;
    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    if (ray->ray_dir_x < 0)
	{
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    } else
	{
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
	{
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    } else
	{
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
    while (ray->hit == 0)
	{
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else
		{
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (ray->side == 0)
		color = 0xFF0000;
	else
		color = 0x0000FF;
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

int	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;
	double	camera_x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		ray.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		ray.hit = 0;
		cast_ray(game, &ray, x);
		draw_column(game, x, &ray);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img, 0, 0);
	return (0);
}
