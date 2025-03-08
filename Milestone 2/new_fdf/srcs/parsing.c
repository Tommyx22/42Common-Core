/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:39:55 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/08 16:10:27 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point parse_point(char *str)
{
    t_point point;
    char **parts;
    
    point.color = C_TEXT;
    
    if (ft_strchr(str, ','))
    {
        parts = ft_split(str, ',');
        point.z = ft_atoi(parts[0]);
        
        if (parts[1] && ft_strncmp(parts[1], "0x", 2) == 0)
            point.color = ft_atoi_base_fdf(parts[1] + 2, 16);
        
        for (int i = 0; parts[i]; i++)
            free(parts[i]);
        free(parts);
    }
    else
    {
        point.z = ft_atoi(str);
    }
    
    return point;
}

// Utility function to convert hex string to integer
int ft_atoi_base_fdf(char *str, int base)
{
    int result = 0;
    int digit;
    
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else if (*str >= 'a' && *str <= 'f')
            digit = *str - 'a' + 10;
        else if (*str >= 'A' && *str <= 'F')
            digit = *str - 'A' + 10;
        else
            break;
            
        if (digit >= base)
            break;
            
        result = result * base + digit;
        str++;
    }
    
    return result;
}

void remove_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int count_words(char *line)
{
    int count = 0;
    int in_word = 0;

    while (*line) {
        if (*line == ' ') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        line++;
    }
    return count;
}

void parse(char **ag, t_vars *vars)
{
    int fd = open(ag[1], O_RDONLY);
    char *line;
    int line_count = 0;

    if (fd == -1) {
        perror("Failed to open file");
        free(vars);  // Free the vars struct on error
        exit(1);
    }

    // First pass to count lines and validate width
    line = get_next_line(fd);
    if (!line) {
        printf("Error: Empty file\n");
        close(fd);
        free(vars);  // Free the vars struct on error
        exit(1);
    }

    vars->width = count_words(line);
    free(line);
    line_count++;

    // Count remaining lines
    while ((line = get_next_line(fd)) != NULL) {
        if (count_words(line) != vars->width) {
            printf("Error: Inconsistent map width\n");
            free(line);
            close(fd);
            free(vars);  // Free the vars struct on error
            exit(1);
        }
        free(line);
        line_count++;
    }

    close(fd);
    vars->height = line_count;

    // Allocate memory for points
    vars->points = malloc(sizeof(t_point*) * vars->height);
    if (!vars->points) {
        printf("Memory allocation failed\n");
        free(vars);  // Free the vars struct on error
        exit(1);
    }

    for (int i = 0; i < vars->height; i++) {
        vars->points[i] = malloc(sizeof(t_point) * vars->width);
        if (!vars->points[i]) {
            // Cleanup previously allocated memory
            for (int j = 0; j < i; j++)
                free(vars->points[j]);
            free(vars->points);
            free(vars);
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    // Reopen file and read lines
    fd = open(ag[1], O_RDONLY);
    line_count = 0;

    while ((line = get_next_line(fd)) != NULL) {
        char **values = ft_split(line, ' ');
        
        for (int i = 0; i < vars->width; i++) {
            vars->points[line_count][i] = parse_point(values[i]);
        }
        
        // Free split results and line
        for (int i = 0; values[i]; i++)
            free(values[i]);
        free(values);
        free(line);
        
        line_count++;
    }

    close(fd);
}

// Updated function to free all resources
int close_s(t_vars *vars)
{
    if (vars) {
        if (vars->points) {
            for (int i = 0; i < vars->height; i++)
                free(vars->points[i]);
            free(vars->points);
        }
        
        if (vars->win && vars->mlx)
            mlx_destroy_window(vars->mlx, vars->win);
        
        if (vars->mlx) {
            mlx_destroy_display(vars->mlx);
            free(vars->mlx);
        }
        
        free(vars);
    }
    exit(0);
    return (0);
}
