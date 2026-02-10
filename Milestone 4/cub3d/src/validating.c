/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/10 15:38:19 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	take_texture(char *line, char **path)
{
	char	*trimmed;

	if (*path != NULL)
		return (ft_putstr_fd("Error\nDouble initialization texture\n", 2), 0);
	trimmed = skip_spaces(line);
	if (!trimmed || *trimmed == '\0')
		return (ft_putstr_fd("Error\nInvalid texture path\n", 2), 0);
	if (!ft_strrchr(trimmed, '.'))
		return (ft_putstr_fd("Error\nInvalid texture path\n", 2), 0);
	if (ft_strcmp(ft_strrchr(trimmed, '.'), ".xpm") != 0)
		return (ft_putstr_fd("Error\nInvalid texture path\n", 2), 0);
	*path = ft_strdup(trimmed);
	if (!*path)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
	return (1);
}

static int	take_element(char *line, t_map *map)
{
	char	*s;

	s = skip_spaces(line);
	if (ft_strncmp(s, "NO ", 3) == 0)
		return (take_texture(s + 3, &map->no_path));
	else if (ft_strncmp(s, "SO ", 3) == 0)
		return (take_texture(s + 3, &map->so_path));
	else if (ft_strncmp(s, "WE ", 3) == 0)
		return (take_texture(s + 3, &map->we_path));
	else if (ft_strncmp(s, "EA ", 3) == 0)
		return (take_texture(s + 3, &map->ea_path));
	else if (ft_strncmp(s, "F ", 2) == 0)
		return (take_color(s + 2, &map->floor));
	else if (ft_strncmp(s, "C ", 2) == 0)
		return (take_color(s + 2, &map->ceiling));
	return (-1);
}

static int	take_map(char **lines, t_map *map, int start)
{
	int	i;
	int	len;
	int	y;
	int	x;

	while (lines[start] && is_empty_line(lines[start]))
		start++;
	if (!lines[start])
		return (ft_putstr_fd("Error\nNo map content found\n", 2), 0);
	i = start;
	map->height = 0;
	map->width = 0;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		len = ft_strlen(lines[i]);
		if (len > map->width)
			map->width = len;
		map->height++;
		i++;
	}
	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
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

static int	read_and_parse(char *file, t_game *game)
{
	int		fd;
	int		i;
	int		ret;
	char	*line;
	char	**lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 0);
	i = 0;
	lines = (char **)ft_calloc(4096, sizeof(char *));
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
			return (ft_free_split(lines), 0);
		if (ret == -1)
			break ;
		i++;
	}
	if (!game->map.no_path || !game->map.so_path || !game->map.we_path
		|| !game->map.ea_path || !game->map.floor.set
		|| !game->map.ceiling.set)
	{
		ft_free_split(lines);
		return (ft_putstr_fd("Error\nMissing texture or color\n", 2), 0);
	}
	ret = take_map(lines, &game->map, i);
	ft_free_split(lines);
	return (ret);
}

int	parse_cub(char *file, t_game *game)
{
	char	*type;

	type = ft_strrchr(file, '.');
	if (!type || ft_strcmp(type, ".cub") != 0)
		return (ft_putstr_fd("Error\nInvalid type\n", 2), ERROR);
	ft_bzero(&game->map, sizeof(t_map));
	game->map.player_x = -1;
	game->map.player_y = -1;
	if (!read_and_parse(file, game))
		return (ERROR);
	if (!validate_map(&game->map))
		return (ERROR);
	if (!game->map.player_dir)
		return (ft_putstr_fd("Error\nMissed player\n", 2), ERROR);
	return (SUCCESS);
}
