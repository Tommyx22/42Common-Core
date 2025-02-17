#include "../includes/fdf.h"

static void	close_coordinates(t_point **coordinates, int width)
{
	int i;

	i = 0;
	while (i < width)
		free(coordinates[i++]);
	free(coordinates);
}

static void	close_fdf_all(t_fdf *fdf, int cleanup)
{
    close_coordinates(fdf->map->coordinates, fdf->map->max_x);
    free(fdf->map);
    if (cleanup)
    {
        mlx_destroy_image(fdf->mlx, fdf->image->image);
        free(fdf->image);
        free(fdf->cam);
    }
    mlx_destroy_window(fdf->mlx, fdf->win);
    mlx_destroy_display(fdf->mlx);
    free(fdf->mlx);
    free(fdf);
}

int	close_all(t_fdf *fdf)
{
    close_fdf_all(fdf, 1);
    write(1, "error code: 1", 13);
    return (0);
}

void	close_map (t_fdf *fdf)
{
	close_fdf_all(fdf, 0);
	write(1, "error code: 0", 13);
}
