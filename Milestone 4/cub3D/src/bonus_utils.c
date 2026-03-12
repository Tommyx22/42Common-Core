/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:08:30 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:19:49 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_game *game, t_square square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			my_mlx_pixel_put(game, square.x + j, square.y + i, square.color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_game *game, int scale, t_square *square)
{
	square->x = game->player.x * scale;
	square->y = game->player.y * scale;
	square->size = 3;
	square->color = 0x000000;
	draw_square(game, *square);
}

void	draw_minimap(t_game *game)
{
	int			x;
	int			y;
	int			scale;
	t_square	square;

	scale = 20;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '1')
			{
				square.x = x * scale;
				square.y = y * scale;
				square.size = scale;
				square.color = 0xFF0000;
				draw_square(game, square);
			}
			x++;
		}
		y++;
	}
	draw_player_minimap(game, scale, &square);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x = -1;
	int			diff;

	(void)y;
	if (old_x == -1)
		old_x = x;
	diff = x - old_x;
	rotate_player(game, diff * 0.005);
	old_x = x;
	return (0);
}
