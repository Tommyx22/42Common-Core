/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:14:34 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/10 15:48:49 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	if (game->mlx.mlx && game->img)
	{
		mlx_destroy_image(game->mlx.mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx.mlx)
		destroy_all_texture(game);
	if (game->mlx.mlx && game->mlx.win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		game->mlx.win = NULL;
	}
	free_map(&game->map);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		game->mlx.mlx = NULL;
	}
	game->addr = NULL;
	exit(0);
	return (0);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 0.2;
	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (game->map.grid[(int)new_y][(int)(new_x + buffer)] != '1' &&
		game->map.grid[(int)new_y][(int)(new_x - buffer)] != '1' &&
		game->map.grid[(int)(new_y + buffer)][(int)new_x] != '1' &&
		game->map.grid[(int)(new_y - buffer)][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

void	strafe_player(t_game *game, double strafe_speed, int direction)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = game->player.dir_y * strafe_speed * direction;
	strafe_y = -game->player.dir_x * strafe_speed * direction;
	move_player(game, strafe_x, strafe_y);
}
