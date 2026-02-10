/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:08:30 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/07 15:16:35 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	scale;

	scale = 20;
	for (int y = 0; y < game->map.height; y++)
	{
		for (int x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == '1')
				draw_square(game, x*scale, y*scale, scale, 0xFF0000);
		}
	}
	draw_square(game, game->player.x*scale, game->player.y*scale, 3, 0x00FF00);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x;
	int			diff;

	old_x = 0;
	(void)y;
	if (old_x == 0)
		old_x = x;
	diff = x - old_x;
	rotate_player(game, diff * 0.005);
	old_x = x;
	return (0);
}
