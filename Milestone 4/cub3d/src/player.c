/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:31:24 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/07 15:08:51 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	set_player_south(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

void	set_player_east(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

void	set_player_west(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}

void	init_player(t_game *game)
{
	game->player.x = game->map.player_x + 0.5;
	game->player.y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
		set_player_north(game);
	else if (game->map.player_dir == 'S')
		set_player_south(game);
	else if (game->map.player_dir == 'E')
		set_player_east(game);
	else if (game->map.player_dir == 'W')
		set_player_west(game);
}
