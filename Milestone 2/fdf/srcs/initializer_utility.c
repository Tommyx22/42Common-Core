#include "../includes/fdf.h"

t_point **init_coordinates(int width, int depth)
{
    t_point **coordinates;
    int     i;
    int     j;

    i = 0;
    coordinates = ft_calloc(width, sizeof(t_point *));
    while (i < width)
    {
        coordinates[i] = ft_calloc(depth, sizeof(t_point *));
        j = 0;
        while (j < depth)
        {
            coordinates[i][j].x = 0;
            coordinates[i][j].y = 0;
            coordinates[i][j].z = 0;
            coordinates[i][j].color = 0;
            j++;
        }
        i++;
    }
    return (coordinates);
}

void    origin(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->max_y)
    {
        x = 0;
        while (x < map->max_x)
        {
            map->coordinates[x][y].x -= map->max_x / 2;
			map->coordinates[x][y].y -= map->max_y / 2;
            x++;
        }
        y++;
    }
}

float	scale_to_fit(t_map *map)
{
	float	scale_x;
	float	scale_y;
	float	scale;

	scale_x = WINDOW_WIDTH / map->max_x;
	scale_y = WINDOW_HEIGHT / map->max_y;
	scale = min(scale_x, scale_y);
	if (scale < 4)
		return (2);
	return (scale / 2);
}

void	reset(t_fdf *fdf)
{
	fdf->cam->scale = scale_to_fit(fdf->map);
	fdf->cam->scale_z = 1;
	fdf->cam->move_x = WINDOW_WIDTH / 2;
	fdf->cam->move_y = WINDOW_HEIGHT / 2;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
}
