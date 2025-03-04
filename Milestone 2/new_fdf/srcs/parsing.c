/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:39:55 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/04 19:01:05 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void format_matrix(char **matrix) {
	
    int max_length = 0;
    int i = 0;

    while (matrix[i] != NULL) {
        int row_length = ft_strlen(matrix[i]);
        if (row_length > max_length) {
            max_length = row_length;
        }
        i++;
    }

    i = 0;
    while (matrix[i] != NULL) {
        int row_length = ft_strlen(matrix[i]);
        if (row_length < max_length) {
            int diff = max_length - row_length;
            char *new_row = malloc(max_length + 1);

            ft_strlcpy(new_row, matrix[i], row_length + 1);
            int j = row_length;
            while (j < max_length) {
                new_row[j] = '0';
                j++;
            }
            new_row[max_length] = '\0';

            printf("%s\n", new_row);
            free(new_row);
        } else {
            printf("%s\n", matrix[i]);
        }
        i++;
    }
}


void parse(int ac, char **ag)
{
    char **map;
    int fd = open(ag[1], O_RDONLY);
    char *line;
    int i = 0;

    if (fd == -1)
    {
        perror("Failed to open file");
        return;
    }

    int line_count = 0;
    line = get_next_line(fd);

    while (line != NULL)
    {
        line_count++;
        free(line);
        line = get_next_line(fd);
    }

    close(fd);

    map = malloc(sizeof(char*) * (line_count + 1));
    if (map == NULL)
    {
        return;
    }

    fd = open(ag[1], O_RDONLY);
    i = 0;

    line = get_next_line(fd);
    while (line != NULL)
    {
        map[i] = line;
        
        i++;
        line = get_next_line(fd);
    }

    map[i] = NULL;

	format_matrix(map);
	
    close(fd);
	int j = 0;
	while (j < line_count)
	{
		free(map[j]);
		j++;
	}
	free(map);
}
/*
void parse(int ac, char **ag)
{
	int **map;
	int	fd = open(ag[1], O_RDONLY);
	char *line;
	int i = 0;
	line = get_next_line(fd);
	while(line != NULL)
	{
		map[i] = line;
		printf("%s\n", map[i]);
		free (line);
		line = get_next_line(fd);
		i++;
	}
	close (fd);
	return;
}
*/
int main(int ac, char **ag)
{
	parse(ac, ag);
}

