#include "../includes/fdf.h"

void	scale(t_line *line, int scale)
{
	line->start.x *= scale;
	line->start.y *= scale;
	line->end.x *= scale;
	line->end.y *= scale;
}

void	translate(t_line *line, int move_x, int move_y)
{
	line->start.x += move_x;
	line->start.y += move_y;
	line->end.x += move_x;
	line->end.y += move_y;
}

void	transform(t_cam *cam, t_line *line)
{
	scale(line, cam->scale);
	translate(line, cam->move_x, cam->move_y);
}
