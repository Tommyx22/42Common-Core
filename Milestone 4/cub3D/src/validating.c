/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:20:11 by tolanini         ###   ########.fr       */
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

int	take_element(char *line, t_map *map)
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
	while (lines[start] && is_empty_line(lines[start]))
		start++;
	if (!lines[start])
		return (ft_putstr_fd("Error\nNo map content found\n", 2), 0);
	calculate_map_dimensions(lines, start, map);
	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 0);
	if (!fill_map_grid(lines, map, start))
		return (0);
	return (1);
}

static int	read_and_parse(char *file, t_game *game)
{
	char	**lines;
	int		map_start;

	lines = read_file_to_lines(file);
	if (!lines)
		return (0);
	map_start = process_config_elements(lines, game);
	if (map_start == -1)
		return (ft_free_split(lines), 0);
	if (!check_required_fields(game))
		return (ft_free_split(lines), 0);
	if (!take_map(lines, &game->map, map_start))
		return (ft_free_split(lines), 0);
	ft_free_split(lines);
	return (1);
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
