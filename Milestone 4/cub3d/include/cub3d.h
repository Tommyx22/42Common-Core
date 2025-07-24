/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:41:53 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/10 16:08:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define WINDOW_WIDTH		1200
# define WINDOW_HEIGHT		900

# define KEY_ESC			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_vars;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_game
{
	t_vars		mlx;
	t_map		map;
	t_player	player;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_game;

// Engine functions
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void		cast_ray(t_game *game, t_ray *ray, int x);
void		draw_column(t_game *game, int x, t_ray *ray);
int			render_frame(t_game *game);

// Player functions
void		init_player(t_game *game);

#endif