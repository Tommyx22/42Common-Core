/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:46:29 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/12 17:54:28 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	bresenham(t_vars *vars, t_point p1, t_point p2)
{
	t_bres	b;
	double	t;
	int		color;

	init_bresenham(p1, p2, &b);
	b.p2 = p2;
	while (1)
	{
		if (b.dist > 0)
			t = b.step / b.dist;
		else
			t = 0;
		color = color_lerp(p1.color, p2.color, t);
		if (b.current.x >= 0 && b.current.x < WINDOW_WIDTH
			&& b.current.y >= 0 && b.current.y < WINDOW_HEIGHT)
			mlx_pixel_put(vars->mlx, vars->win,
				b.current.x, b.current.y, color);
		if (b.current.x == p2.x && b.current.y == p2.y)
			break ;
		update_bresenham(&b);
	}
}

void	transform_point(t_vars *vars, t_point *p, int x, int y)
{
	float	z;

	z = p->z;
	p->x = x;
	p->y = y;
	p->x *= vars->camera.zoom;
	p->y *= vars->camera.zoom;
	check_camera(vars, p, z);
	p->x += vars->camera.x_offset;
	p->y += vars->camera.y_offset;
}

void	find_z_range(t_vars *vars, int *min_z, int *max_z)
{
	int	y;
	int	x;

	*min_z = INT_MAX;
	*max_z = INT_MIN;
	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (vars->points[y][x].z < *min_z)
				*min_z = vars->points[y][x].z;
			if (vars->points[y][x].z > *max_z)
				*max_z = vars->points[y][x].z;
			x++;
		}
		y++;
	}
}

void	draw_map(t_vars *vars)
{
	int		min_z;
	int		max_z;
	int		y;
	int		x;

	find_z_range(vars, &min_z, &max_z);
	mlx_clear_window(vars->mlx, vars->win);
	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			draw_line(x, y, vars);
			x++;
		}
		y++;
	}
}
