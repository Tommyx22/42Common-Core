/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:33:18 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/09 15:56:42 by tolanini         ###   ########.fr       */
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

static void	destroy_texture(t_game *game, t_texture *tex)
{
	if (tex->img)
	{
		mlx_destroy_image(game->mlx.mlx, tex->img);
		tex->img = NULL;
	}
}

void	destroy_all_texture(t_game *game)
{
	destroy_texture(game, &game->tex_north);
	destroy_texture(game, &game->tex_south);
	destroy_texture(game, &game->tex_east);
	destroy_texture(game, &game->tex_west);
}
