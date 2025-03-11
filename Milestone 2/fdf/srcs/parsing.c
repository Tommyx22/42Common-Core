/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:39:55 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/11 20:35:03 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	parse_point(char *str)
{
	t_point	point;
	char	**parts;
	int		i;

	point.color = C_TEXT;
	if (!str)
		return (point);
	if (ft_strchr(str, ','))
	{
		parts = ft_split(str, ',');
		if (parts && parts[0])
			point.z = ft_atoi(parts[0]);
		if (parts && parts[1] && ft_strncmp(parts[1], "0x", 2) == 0)
			point.color = ft_atoi_base_fdf(parts[1] + 2, 16);
		i = -1;
		if (parts)
		{
			while (parts[++i])
				free(parts[i]);
			free(parts);
		}
	}
	else
		point.z = ft_atoi(str);
	return (point);
}

int	ft_atoi_base_fdf(char *str, int base)
{
	int	result;
	int	digit;

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	return (result);
}

void	remove_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	count_words(char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		line++;
	}
	return (count);
}

void	parse(char **ag, t_vars *vars)
{
	int		fd;
	char	*line;
	int		line_count;
	char	**values;

	values = NULL;
	fd = open(ag[1], O_RDONLY);
	check_fd(fd, vars);
	line_count = 0;
	line = get_next_line(fd);
	check_line(line, fd, vars);
	vars->width = count_words(line);
	free(line);
	line_count++;
	line = get_next_line(fd);
	generic_util(line, vars, fd, line_count);
	fd = open(ag[1], O_RDONLY);
	line_count = 0;
	line = get_next_line(fd);
	convert_map(line, vars, values, fd);
	close(fd);
}
