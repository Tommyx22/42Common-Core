/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:20:14 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
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
	if (init_mlx(&game) == ERROR)
		return (close_game(&game), 1);
	if (load_all_textures(&game) == ERROR)
		return (close_game(&game), 1);
	init_player(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
