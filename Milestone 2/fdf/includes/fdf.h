#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include "keys.h"
# include "colors.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	float	transform_z;
}	t_line;

typedef struct s_color
{
	int	start_color;
	int	start_r;
	int	start_g;
	int	start_b;
	int	end_color;
	int	end_r;
	int	end_g;
	int	end_b;
	int	delta_r;
	int	delta_g;
	int	delta_b;
}	t_color;

typedef struct s_map
{
	t_point	**coordinates;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct s_image
{
	void	*image;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
	t_line	*line;
}	t_image;

typedef struct s_cam
{
	int		projection;
	int		color_Pal;
	float	scale;
	float	scale_z;
	float	move_x;
	float	move_y;
	double	alpha;
	double	beta;
	double	gamma;
}	t_cam;

typedef struct s_fdf
{
	t_map	*map;
	void	*mlx;
	int		win_x;
	int		win_y;
	void	*win;
	t_image	*image;
	t_cam	*cam;
}	t_fdf;

enum e_projection
{
	ISOMETRIC,
	PERSPECTIVE,
	TOP
};

enum e_bool
{
	FALSE,
	TRUE
};

# define WINDOW_NAME	 	"fdf"
# define WINDOW_WIDTH		1200
# define WINDOW_HEIGHT		900
# define MAX_PIXEL			1080000

# define HEXADECIMAL_L_BASE	"0123456789abcdef"
# define ANG_1				0.01745329
# define ANG_30				0.52359877
# define ANG_45				0.78539816

# define LINE_DEFAULT		C_WHITE
# define BACKGROUND_DEFAULT	C_GREY
# define C_TEXT				C_WHITE


int		close_all(t_fdf *fdf);
void		close_map(t_fdf *fdf);
t_color	*color_Pal_init(int min_color, int max_color);
t_color	*color_init(t_point start, t_point end);
int	get_color(t_color *color, int i_line, int line_size);
void	pixel_to_image(t_image *image, int x, int y, int color);
void	bresenham(t_fdf *fdf, t_point start, t_point end);
void	clear_image(t_image *image, int image_size);
t_point **init_coordinates(int width, int depth);
void	origin(t_map *map);
float	scale_to_fit(t_map *map);
void	reset(t_fdf *fdf);
t_map   *init_map(void);
t_image *init_image(void *mlx);
t_cam	*init_cam(t_map *map);
t_line	*init_line(t_point start, t_point end, t_fdf *fdf);
t_fdf   *init_project(char  *file_name);
void	print_instruction(t_fdf *fdf);
int key_pressed(int keycode, t_fdf *fdf);
t_map   *read_map(char *file_name);
void	render(t_fdf *fdf);
void	rotate(t_cam *cam, t_line *line);
void	rotate_x(t_line line, double angle);
void    rotate_y(t_line line, double angle);
void	rotate_z(t_line line, double angle);
void	scale(t_line *line, int scale);
void	translate(t_line *line, int move_x, int move_y);
void	transform(t_cam *cam, t_line *line);
float	absolute(float nbr);
float	max(float a, float b);
float	min(float a, float b);
void	fdf_views(t_cam *cam, t_line *line);
size_t	ft_split_count(const char *s, char c);

#endif