/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:22:28 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/11 17:45:40 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	check_fd(int fd, t_vars *vars)
{
	if (fd == -1)
	{
		perror("Failed to open file");
		free(vars);
		exit(1);
	}
}

void	check_line(char *line, int fd, t_vars *vars)
{
	if (!line)
	{
		printf("Error: Empty file\n");
		close(fd);
		free(vars);
		exit(1);
	}
}

void	check_map(char *line, t_vars *vars, int fd)
{
	if (count_words(line) != vars->width)
	{
		printf("Error: Inconsistent map width\n");
		free(line);
		close(fd);
		free(vars);
		exit(1);
	}
}

void	check_memory(t_vars *vars, int i)
{
	if (!vars->points[i])
	{
		while (i > 0)
		{
			i--;
			free(vars->points[i]);
		}
		free(vars->points);
		free(vars);
		printf("Memory allocation failed\n");
		exit(1);
	}
}
