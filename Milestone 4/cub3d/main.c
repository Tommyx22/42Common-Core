/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/10 16:34:37 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	if (ac != 2)
		return (printf("Error: Usage: ./cub3d <map.cub>\n"), 1);
	if (parse_map(av[1], &game.map) == ERROR)
		return (printf("Error: Invalid parsing of the map"), 1);
	game.mlx.mlx = mlx_init();
	game.mlx.win = mlx_new_window(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	game.img = mlx_new_image(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_len,
			&game.endian);
	init_player(&game);
	mlx_loop_hook(game.mlx.mlx, render_frame, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
