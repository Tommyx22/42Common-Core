/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:41 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/12 17:15:02 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_menu(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "How to use:");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Zoom: + / -");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Move: Arrow Keys");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Rotate X: W / S");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Rotate Y: A / D");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Rotate Z: Q / E");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Z-scale: Page Up / Down");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "View:I(isometric)/T(top)");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Reset: R");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Exit: ESC");
}

void	x_point_drawing(int y, int x, t_vars *vars, t_point p1)
{
	t_point	p2;

	p2.z = vars->points[y][x + 1].z;
	if (vars->camera.projection == TOP_VIEW
		&& vars->points[y][x + 1].color == C_TEXT)
		p2.color = C_TEXT;
	else
		p2.color = vars->points[y][x + 1].color;
	transform_point(vars, &p2, x + 1, y);
	bresenham(vars, p1, p2);
}

void	y_point_drawing(int y, int x, t_vars *vars, t_point p1)
{
	t_point	p2;

	p2.z = vars->points[y + 1][x].z;
	if (vars->camera.projection == TOP_VIEW
		&& vars->points[y + 1][x].color == C_TEXT)
		p2.color = C_TEXT;
	else
		p2.color = vars->points[y + 1][x].color;
	transform_point(vars, &p2, x, y + 1);
	bresenham(vars, p1, p2);
}

void	draw_line(int x, int y, t_vars *vars)
{
	t_point	p1;

	p1.z = vars->points[y][x].z;
	if (vars->camera.projection == TOP_VIEW
		&& vars->points[y][x].color == C_TEXT)
		p1.color = C_TEXT;
	else
		p1.color = vars->points[y][x].color;
	transform_point(vars, &p1, x, y);
	if (x + 1 < vars->width)
		x_point_drawing(y, x, vars, p1);
	if (y + 1 < vars->height)
		y_point_drawing(y, x, vars, p1);
}
