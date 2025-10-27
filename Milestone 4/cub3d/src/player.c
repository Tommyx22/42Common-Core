/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:31:24 by tolanini          #+#    #+#             */
/*   Updated: 2025/10/27 14:38:34 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_direction(t_player *player, double dir_x, double dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

static void	init_player_plane(t_player *player, double plane_x, double plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void	init_player(t_game *game)
{
	game->player.x = game->map.player_x + 0.5;
	game->player.y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
	{
		init_player_direction(&game->player, 0, -1);
		init_player_plane(&game->player, 0.66, 0);
	}
	else if (game->map.player_dir == 'S')
	{
		init_player_direction(&game->player, 0, 1);
		init_player_plane(&game->player, -0.66, 0);
	}
	else if (game->map.player_dir == 'E')
	{
		init_player_direction(&game->player, 1, 0);
		init_player_plane(&game->player, 0, 0.66);
	}
	else if (game->map.player_dir == 'W')
	{
		init_player_direction(&game->player, -1, 0);
		init_player_plane(&game->player, 0, -0.66);
	}
}
