/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:54:40 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/08 17:46:24 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define WINDOW_WIDTH		1200
# define WINDOW_HEIGHT		900
# define OFFSET_X			680
# define OFFSET_Y			290
# define SCALE_FACTOR		25
# define Z_SCALE			10
# define C_TEXT				0xffffff

# define ISOMETRIC			0
# define TOP_VIEW			1

# define KEY_ESC			65307
# define KEY_PLUS			61
# define KEY_MINUS			45
# define KEY_NUM_PLUS		65451
# define KEY_NUM_MINUS		65453
# define KEY_UP				65362
# define KEY_DOWN			65364
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_Q				113
# define KEY_E				101
# define KEY_I				105
# define KEY_T				116
# define KEY_R				114
# define KEY_PAGE_UP		65365
# define KEY_PAGE_DOWN		65366

typedef struct s_point
{
	int		z;
	int		color;
	int		x;
	int		y;
} t_point;

typedef struct s_cam
{
	float	x_offset;
	float	y_offset;
	float	z_scale;
	float	zoom;
	float	alpha;
	float	beta;
	float	gamma;
	int		projection;
} t_cam;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_point	**points;
	int		height;
	int		width;
	t_cam	camera;
}	t_vars;

// Function prototypes
void	parse(char **ag, t_vars *vars);
void	remove_spaces(char *str);
int		ft_atoi_base_fdf(char *str, int base);
t_point	parse_point(char *str);

// Drawing functions
void	bresenham(t_vars *vars, t_point p1, t_point p2);
void	transform_point(t_vars *vars, t_point *p, int x, int y);
void	draw_map(t_vars *vars);
void	draw_menu(t_vars *vars);
int		color_lerp(int c1, int c2, double t);

// Camera functions
void	init_camera(t_cam *camera);
void	zoom(int key, t_vars *vars);
void	move(int key, t_vars *vars);
void	rotate(int key, t_vars *vars);
void	change_projection(int key, t_vars *vars);
void	change_z_scale(int key, t_vars *vars);
void	reset_camera(t_vars *vars);

// Utility functions
int		close_s(t_vars *vars);

#endif