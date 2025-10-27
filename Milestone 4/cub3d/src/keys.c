/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:14:34 by tolanini          #+#    #+#             */
/*   Updated: 2025/10/27 15:33:51 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	exit(0);
	return (0);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	
	// Check if new position is not a wall
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
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

int	key_press(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.1;
	
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		move_player(game, game->player.dir_x * move_speed, 
			game->player.dir_y * move_speed);
	else if (keycode == KEY_S)
		move_player(game, -game->player.dir_x * move_speed, 
			-game->player.dir_y * move_speed);
	else if (keycode == KEY_A)
		strafe_player(game, move_speed, 1);  // Strafe left
	else if (keycode == KEY_D)
		strafe_player(game, move_speed, -1); // Strafe right
	else if (keycode == KEY_LEFT)
		rotate_player(game, rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, -rot_speed);
	return (0);
}