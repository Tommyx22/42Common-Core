/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/06 12:00:00 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_char(t_map *map)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] != '0' && map->grid[y][x] != '1'
				&& map->grid[y][x] != ' ' && map->grid[y][x] != 'N'
				&& map->grid[y][x] != 'S' && map->grid[y][x] != 'E'
				&& map->grid[y][x] != 'W')
				return (ft_putstr_fd("Error\nInvalid character in map\n",
						2), 0);
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				map->player_dir = map->grid[y][x];
				map->player_x = x;
				map->player_y = y;
				map->grid[y][x] = '0';
				count++;
			}
		}
	}
	if (count != 1)
		return (ft_putstr_fd("Error\nMap must have exactly one player\n",
				2), 0);
	return (1);
}

static int	is_wall(t_map *map, int y, int x)
{
	if (map->grid[y][x] != '0')
		return (1);
	if (y == 0 || y == map->height - 1 || x == 0 || x >= map->width - 1)
		return (ft_putstr_fd("Error\nInvalid wall\n", 2), 0);
	if (x >= (int)ft_strlen(map->grid[y - 1])
		|| map->grid[y - 1][x] == ' ')
		return (ft_putstr_fd("Error\nInvalid wall\n", 2), 0);
	if (x >= (int)ft_strlen(map->grid[y + 1])
		|| map->grid[y + 1][x] == ' ')
		return (ft_putstr_fd("Error\nInvalid wall\n", 2), 0);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (ft_putstr_fd("Error\nInvalid wall\n", 2), 0);
	return (1);
}

static int	flood_fill(char **grid, int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (grid[y][x] == ' ')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'F')
		return (1);
	grid[y][x] = 'F';
	if (!flood_fill(grid, x + 1, y, map))
		return (0);
	if (!flood_fill(grid, x - 1, y, map))
		return (0);
	if (!flood_fill(grid, x, y + 1, map))
		return (0);
	if (!flood_fill(grid, x, y - 1, map))
		return (0);
	return (1);
}

static int	check_map_closed(t_map *map)
{
	char	**copy;
	int		y;
	int		ret;

	copy = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!copy)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
	y = -1;
	while (++y < map->height)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
			return (ft_free_split(copy),
				ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
	}
	copy[map->height] = NULL;
	ret = flood_fill(copy, map->player_x, map->player_y, map);
	ft_free_split(copy);
	if (!ret)
		return (ft_putstr_fd("Error\nMap is not closed by walls\n", 2), 0);
	return (1);
}

int	validate_map(t_map *map)
{
	int	y;
	int	x;

	if (!validate_char(map))
		return (0);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!is_wall(map, y, x))
				return (0);
		}
	}
	if (!check_map_closed(map))
		return (0);
	return (1);
}
