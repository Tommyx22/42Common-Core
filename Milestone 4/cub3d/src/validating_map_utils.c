/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:04:47 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/09 15:56:25 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	process_player_char(t_map *map, int x, int y, int *count)
{
	if (map->grid[y][x] != 'N' && map->grid[y][x] != 'S'
		&& map->grid[y][x] != 'E' && map->grid[y][x] != 'W')
		return (1);
	map->player_dir = map->grid[y][x];
	map->player_x = x;
	map->player_y = y;
	map->grid[y][x] = '0';
	(*count)++;
	return (1);
}
