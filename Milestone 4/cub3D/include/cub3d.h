/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:41:53 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/12 17:19:43 by tolanini         ###   ########.fr       */
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

# define WINDOW_WIDTH		1920
# define WINDOW_HEIGHT		1080

# define KEY_ESC		65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# define ERROR		-1
# define SUCCESS	1

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	set;
}	t_color;

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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_color	floor;
	t_color	ceiling;
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

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_draw_col
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			y;
	int			color;
	double		step;
	double		tex_pos;
	t_texture	*tex;
}	t_draw_col;

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
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_east;
	t_texture	tex_west;
}	t_game;

// Engine functions
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void		cast_ray(t_game *game, t_ray *ray, int x);
void		draw_textured_column(t_game *game, int x, t_ray *ray);
int			render_frame(t_game *game);
int			init_mlx(t_game *game);
void		setup_hooks(t_game *game);

// Engine utility functions
void		init_ray(t_game *game, t_ray *ray, int x);
void		calculate_x_y(t_game *game, t_ray *ray);
void		perform_dda(t_game *game, t_ray *ray);
void		calculate_wall_dist(t_game *game, t_ray *ray);
void		calculate_column_bounds(t_draw_col *col, double perp_wall_dist);
void		select_texture(t_game *game, t_draw_col *col, t_ray *ray);
void		calculate_texture_x(t_game *game, t_draw_col *col, t_ray *ray);
void		setup_texture_sampling(t_draw_col *col);
void		render_column_pixels(t_game *game, int x, t_draw_col *col);
void		draw_ceiling(t_game *game, int ceiling_color);
void		draw_floor(t_game *game, int floor_color);
void		draw_walls(t_game *game);
void		display_frame(t_game *game);

// Player functions
void		init_player(t_game *game);

// Key handling functions
int			key_press(int keycode, t_game *game);
int			close_game(t_game *game);
void		move_player(t_game *game, double move_x, double move_y);
void		rotate_player(t_game *game, double rot_speed);
void		strafe_player(t_game *game, double strafe_speed, int direction);
void		destroy_all_texture(t_game *game);

// Texture rendering
int			load_texture(t_game *game, t_texture *tex, char *path);
int			load_all_textures(t_game *game);
int			get_texture_color(t_texture *tex, int x, int y);
void		draw_textured_column(t_game *game, int x, t_ray *ray);

// Utils like mouse and minimap
int			mouse_move(int x, int y, t_game *game);
void		draw_minimap(t_game *game);
void		draw_square(t_game *game, t_square square);
void		draw_player_minimap(t_game *game, int scale, t_square *square);

// Parsing functions
int			parse_cub(char *file, t_game *game);
int			validate_map(t_map *map);
void		free_map(t_map *map);

// Parsing utility functions
char		*skip_spaces(char *s);
int			is_empty_line(char *line);
int			take_color(char *line, t_color *color);
int			is_valid_int(char *str);
int			rgb_to_int(t_color *color);
char		**parse_rgb_split(char *trimmed);
int			validate_rgb_values(char **rgb, t_color *color);
int			is_valid_map_char(char c);
int			process_player_char(t_map *map, int x, int y, int *count);
void		calculate_map_dimensions(char **lines, int start, t_map *map);
int			fill_map_grid(char **lines, t_map *map, int start);
char		**read_file_to_lines(char *file);
int			process_config_elements(char **lines, t_game *game);
int			check_required_fields(t_game *game);
int			take_element(char *line, t_map *map);

#endif