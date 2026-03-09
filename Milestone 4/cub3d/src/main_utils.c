/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:57:34 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/09 15:56:20 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	game->img = mlx_new_image(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	return (SUCCESS);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx.win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx.mlx, render_frame, game);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->tex_north, game->map.no_path)
		|| !load_texture(game, &game->tex_south, game->map.so_path)
		|| !load_texture(game, &game->tex_east, game->map.ea_path)
		|| !load_texture(game, &game->tex_west, game->map.we_path))
	{
		printf("Error: Cannot load textures\n");
		return (ERROR);
	}
	return (SUCCESS);
}
