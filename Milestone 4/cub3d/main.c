/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/03 15:44:42 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_game *game)
{
	// Inizializza la struttura della mappa
	game->map.width = 6;
	game->map.height = 5;
	game->map.player_x = 4;  // Position of 'N'
	game->map.player_y = 2;
	game->map.player_dir = 'W';

	// Alloca memoria per la griglia
	game->map.grid = (char **)ft_calloc(game->map.height + 1, sizeof(char *));
	for (int y = 0; y < game->map.height; y++) {
		game->map.grid[y] = (char *)ft_calloc(game->map.width + 1, sizeof(char));
	}

	// Mappa ESATTAMENTE come fornita, con spazi preservati
	char *fixed_map[] = {
		"111111",
		"100001",
		"1000W1",
		"100001",
		"111111"
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

// int load_textures(t_game *game)
// {
//     if (!load_texture(game, &game->wall_tex, "textures/wall.xpm"))
//         return (0);
//     if (!load_texture(game, &game->floor_tex, "textures/floor.xpm"))
//         return (0);
//     return (1);
// }
int load_textures(t_game *game)
{
    // Load the SAME texture file for all directions (for testing)
    // Later you can replace with different files
    if (!load_texture(game, &game->tex_north, "textures/wall.xpm") ||
        !load_texture(game, &game->tex_south, "textures/wall.xpm") ||
        !load_texture(game, &game->tex_east, "textures/wall.xpm") ||
        !load_texture(game, &game->tex_west, "textures/wall.xpm"))
    {
        return (0);
    }
    
    printf("Loaded same texture for all directions for testing\n");
    return (1);
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
	if (!load_textures(&game))
    {
        printf("Make sure you have textures/wall.xpm and textures/floor.xpm\n");
        return (1);
    }
    init_player(&game);
	mlx_hook(game.mlx.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.mlx.win, 17, 0, close_game, &game);
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