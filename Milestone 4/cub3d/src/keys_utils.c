/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:33:18 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/05 13:33:40 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		strafe_player(game, move_speed, 1);
	else if (keycode == KEY_D)
		strafe_player(game, move_speed, -1);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, rot_speed);
	return (0);
}
