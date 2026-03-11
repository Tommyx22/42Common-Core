/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:33:18 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/11 14:19:57 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
