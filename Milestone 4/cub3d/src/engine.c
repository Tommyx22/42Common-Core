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

void cast_ray(t_game *game, t_ray *ray, int x)
{
    double camera_x;

    camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	
	//DDA
    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
    
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
    
	if (ray->side == 0)
        ray->perp_wall_dist = fabs((ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir_x);
    else
        ray->perp_wall_dist = fabs((ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir_y);
}
		
// void	draw_column(t_game *game, int x, t_ray *ray)
// {
// 	int	line_height;
// 	int	draw_start;
// 	int	draw_end;
// 	int	color;
// 	int	y;

// 	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
// 	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
// 	if (draw_end >= WINDOW_HEIGHT)
// 		draw_end = WINDOW_HEIGHT - 1;
// 	if (ray->side == 0)
// 		color = 0xFF0000;
// 	else
// 		color = 0x0000FF;
// 	y = draw_start;
// 	while (y < draw_end)
// 	{
// 		my_mlx_pixel_put(game, x, y, color);
// 		y++;
// 	}
// }

void draw_textured_column(t_game *game, int x, t_ray *ray)
{
    int     line_height;
    int     draw_start;
    int     draw_end;
    double  wall_x;
    int     tex_x;
    int     tex_y;
    int     y;
    int     color;
    t_texture *tex;

    // Calculate wall height
    line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
    draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;

    // Determine which texture to use based on wall side
    if (ray->side == 0)
    {
        if (ray->ray_dir_x > 0)
            tex = &game->tex_east;
        else
            tex = &game->tex_west;
    }
    else
    {
        if (ray->ray_dir_y > 0)
            tex = &game->tex_south;
        else
            tex = &game->tex_north;
    }
    
    // Calculate texture coordinates
    if (ray->side == 0)
        wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
    
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)tex->width);
    
    // fix texture flipping
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;

    // FIXED: PERSPECTIVE-CORRECT TEXTURE MAPPING
    double step = 1.0 * tex->height / line_height;  // Texture step per screen pixel
    double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
    

    // Draw textured wall
    y = draw_start;
    while (y < draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);  // Wrap texture coordinate
        tex_pos += step;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        color = get_texture_color(tex, tex_x, tex_y);
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
}


// int	render_frame(t_game *game)
// {
// 	t_ray	ray;
// 	int		x;
// 	int		y;
// 	double	camera_x;
	
// 	y = 0;
// 	while (y < WINDOW_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WINDOW_WIDTH)
// 		{
// 			if (y < WINDOW_HEIGHT / 2)
// 				my_mlx_pixel_put(game, x, y, 0x87CEEB);
// 			else
// 				my_mlx_pixel_put(game, x, y, 0x00FF00);
// 			x++;
// 		}
// 		y++;
// 	}
	
// 	x = 0;
// 	while (x < WINDOW_WIDTH)
// 	{
// 		camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
// 		ray.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 		ray.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
// 		ray.hit = 0;
// 		cast_ray(game, &ray, x);
// 		draw_column(game, x, &ray);
// 		x++;
// 	}
// 	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img, 0, 0);
// 	return (0);
// }

int render_frame(t_game *game)
{
    t_ray   ray;
    int     x;
    int     y;
    double  camera_x;

    // Draw sky blue ceiling (top half)
    for (y = 0; y < WINDOW_HEIGHT / 2; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            my_mlx_pixel_put(game, x, y, 0x87CEEB);
        }
    }

    // Draw DARK GREY floor (bottom half)
    for (y = WINDOW_HEIGHT / 2; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            my_mlx_pixel_put(game, x, y, 0x202020); // Dark grey
        }
    }

    // Then draw walls on top
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        ray.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        ray.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
        ray.hit = 0;
        cast_ray(game, &ray, x);
        draw_textured_column(game, x, &ray);
        x++;
    }
    
    draw_minimap(game);

    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img, 0, 0);
    return (0);
}
