/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/07 15:10:13 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Error: Usage: ./cub3d <map.cub>\n"), 1);
	ft_bzero(&game, sizeof(t_game));
	if (parse_cub(av[1], &game) == ERROR)
	{
		free_map(&game.map);
		return (1);
	}
	game.mlx.mlx = mlx_init();
	game.mlx.win = mlx_new_window(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	game.img = mlx_new_image(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_len,
			&game.endian);
	if (!load_texture(&game, &game.tex_north, game.map.no_path) ||
		!load_texture(&game, &game.tex_south, game.map.so_path) ||
		!load_texture(&game, &game.tex_east, game.map.ea_path) ||
		!load_texture(&game, &game.tex_west, game.map.we_path))
	{
		printf("Error: Cannot load textures\n");
		free_map(&game.map);
		return (1);
	}
	init_player(&game);
	mlx_hook(game.mlx.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.mlx.win, 6, 1L<<6, mouse_move, &game);
	mlx_hook(game.mlx.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx.mlx, render_frame, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
