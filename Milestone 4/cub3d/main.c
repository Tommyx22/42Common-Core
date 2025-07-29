/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/29 18:22:21 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_game *game)
{
	// Inizializza la struttura della mappa
	game->map.width = 27;  // Larghezza massima delle righe
	game->map.height = 13; // Numero di righe
	game->map.player_x = 22.5;
	game->map.player_y = 11.5;
	game->map.player_dir = 'N';

	// Alloca memoria per la griglia
	game->map.grid = (char **)ft_calloc(game->map.height + 1, sizeof(char *));
	for (int y = 0; y < game->map.height; y++) {
		game->map.grid[y] = (char *)ft_calloc(game->map.width + 1, sizeof(char));
	}

	// Mappa ESATTAMENTE come fornita, con spazi preservati
	char *fixed_map[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111"
	};

	// Copia la mappa preservando gli spazi
	for (int y = 0; y < game->map.height; y++) {
		int x;
		for (x = 0; x < (int)ft_strlen(fixed_map[y]); x++) {
			game->map.grid[y][x] = fixed_map[y][x];
		}
		// Riempimento per larghezze diverse (con muri per sicurezza)
		while (x < game->map.width) {
			game->map.grid[y][x] = '1';
			x++;
		}
		game->map.grid[y][game->map.width] = '\0';
	}
}

int main(int ac, char **av)
{
    t_game game;
    
    (void)ac;
    (void)av;
    init_map(&game);
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
/*
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
*/