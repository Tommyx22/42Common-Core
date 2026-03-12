/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:09:13 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:20:09 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_map_dimensions(char **lines, int start, t_map *map)
{
	int	i;
	int	len;

	map->height = 0;
	map->width = 0;
	i = start;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		len = ft_strlen(lines[i]);
		if (len > map->width)
			map->width = len;
		map->height++;
		i++;
	}
}

int	fill_map_grid(char **lines, t_map *map, int start)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		map->grid[y] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!map->grid[y])
			return (ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
		x = -1;
		while (++x < (int)ft_strlen(lines[start + y]))
			map->grid[y][x] = lines[start + y][x];
		while (x < map->width)
			map->grid[y][x++] = ' ';
		map->grid[y][map->width] = '\0';
	}
	map->grid[map->height] = NULL;
	return (1);
}

char	**read_file_to_lines(char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	**lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), NULL);
	lines = (char **)ft_calloc(4096, sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	process_config_elements(char **lines, t_game *game)
{
	int	i;
	int	ret;

	i = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		ret = take_element(lines[i], &game->map);
		if (ret == 0)
			return (-1);
		if (ret == -1)
			break ;
		i++;
	}
	return (i);
}

int	check_required_fields(t_game *game)
{
	if (!game->map.no_path || !game->map.so_path || !game->map.we_path
		|| !game->map.ea_path || !game->map.floor.set
		|| !game->map.ceiling.set)
		return (ft_putstr_fd("Error\nMissing texture or color\n", 2), 0);
	return (1);
}
