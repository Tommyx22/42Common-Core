#include "../includes/fdf.h"

static void	apply_colors(t_fdf fdf, t_pointpoint)
{
	t_color	*col;

	col = NULL;
	if (fdf->cam->color_Pal == FALSE)
	{
		if (point->color == -1)
			point->color = LINE_DEFAULT;
	}
	else
	{
		if (point->z >= 0)
		{
			col = color_Pal_init(C_GREY, C_ORANGY);
			point->color = get_color(col, absolute(point->z), \
				absolute(fdf->map->max_z));
			free(col);
		}
		else
		{
			col = color_Pal_init(C_GREY, C_BLUEY);
			point->color = get_color(col, absolute(point->z), \
				absolute(fdf->map->max_z));
			free(col);
		}
	}
}

static void	render_draw_line(t_fdf *fdf, t_point start, t_point end)
{
	start.z *= fdf->cam->scale_z;
	end.z *= fdf->cam->scale_z;
	apply_colors(fdf, &start);
	apply_colors(fdf, &end);
	fdf->image->line = init_line(start, end, fdf);
	if (!fdf->image->line)
		close_all(fdf, 7);
	rotate(fdf->cam, fdf->image->line);
	fdf_views(fdf->cam, fdf->image->line);
	transform(fdf, fdf->image->line);
	brasenham(fdf, fdf->image->line->start, fdf->image->line->end);
	free(fdf->image->line);
}

void	render(t_fdf *fdf)
{
	int x;
	int y;

	clear_image(fdf->image, MAX_PIXEL * 4);
	y = 0;
	while (y < fdf->map->max_y)
	{
		x = 0;
		while (x < fdf->map->max_x)
		{
			if (x < fdf->map->max_x - 1)
				render_draw_line(fdf, fdf->map->coordinates[x][y], fdf->map->coordinates[x + 1][y]);
			if (y < fdf->map->max_y - 1)
				render_draw_line(fdf, fdf->map->coordinates[x][y], fdf->map->coordinates[x][y + 1]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image->image, 0, 0);
	print_instruction(fdf);
}
