/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:46:26 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/11 20:34:07 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	memory_allocation_of_points(t_vars *vars, int line_count)
{
	vars->height = line_count;
	vars->points = malloc(sizeof(t_point *) * vars->height);
	if (!vars->points)
	{
		printf("Memory allocation failed\n");
		free(vars);
		exit(1);
	}
}

void	generic_util(char *line, t_vars *vars, int fd, int line_count)
{
	int	i;

	while (line != NULL)
	{
		check_map(line, vars, fd);
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	close(fd);
	memory_allocation_of_points(vars, line_count);
	i = 0;
	while (i < vars->height)
	{
		vars->points[i] = malloc(sizeof(t_point) * vars->width);
		check_memory(vars, i);
		i++;
	}
}

void	convert_map(char *line, t_vars *vars, char **values, int fd)
{
	int	i;
	int	line_count;

	line_count = 0;
	while (line != NULL)
	{
		values = ft_split(line, ' ');
		i = 0;
		while (i < vars->width)
		{
			vars->points[line_count][i] = parse_point(values[i]);
			i++;
		}
		i = 0;
		while (values[i])
		{
			free(values[i]);
			i++;
		}
		free(values);
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
}
