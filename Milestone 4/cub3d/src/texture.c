/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:15:34 by tolanini          #+#    #+#             */
/*   Updated: 2025/10/28 14:56:26 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int load_texture(t_game *game, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx.mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: Failed to load texture: %s\n", path);
        return (0);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    printf("Loaded texture: %s (%dx%d)\n", path, tex->width, tex->height);
    return (1);
}

int get_texture_color(t_texture *tex, int x, int y)
{
    char    *dst;
    int     color;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0xFF00FF);// magenta texture to debug boundaries
    
    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    color = *(unsigned int *)dst;
    return (color);
}
