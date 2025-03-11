/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:46:29 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/11 20:45:17 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

int	color_lerp(int c1, int c2, double t)
{
	int	r1 = (c1 >> 16) & 0xFF;
	int	g1 = (c1 >> 8) & 0xFF;
	int	b1 = c1 & 0xFF;
	
	int	r2 = (c2 >> 16) & 0xFF;
	int	g2 = (c2 >> 8) & 0xFF;
	int	b2 = c2 & 0xFF;
	
	int	r = r1 + (int)(t * (r2 - r1));
	int	g = g1 + (int)(t * (g2 - g1));
	int	b = b1 + (int)(t * (b2 - b1));
	
	return (r << 16) | (g << 8) | b;
}

void	bresenham(t_vars *vars, t_point p1, t_point p2)
{
	int	dx = abs(p2.x - p1.x);
	int	dy = abs(p2.y - p1.y);
	int	sx = (p1.x < p2.x) ? 1 : -1;
	int	sy = (p1.y < p2.y) ? 1 : -1;
	int	err = dx - dy;
	double	dist = sqrt(dx * dx + dy * dy);
	double	step = 0;
	t_point	current = p1;

	while (1)
	{
		double	t = (dist > 0) ? step / dist : 0;
		int	color = color_lerp(p1.color, p2.color, t);
		if (current.x >= 0 && current.x < WINDOW_WIDTH && 
			current.y >= 0 && current.y < WINDOW_HEIGHT)
			mlx_pixel_put(vars->mlx, vars->win, current.x, current.y, color);
		if (current.x == p2.x && current.y == p2.y)
			break;
		int	e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			current.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			current.y += sy;
		}
		step += 1.0;
	}
}

// Apply all transformations to a point
void	transform_point(t_vars *vars, t_point *p, int x, int y)
{
	// Save original z
	float z = p->z;
	
	// Set screen coordinates
	p->x = x;
	p->y = y;
	
	// Apply zoom
	p->x *= vars->camera.zoom;
	p->y *= vars->camera.zoom;
	
	// Remove automatic centering
	// p->x -= (vars->width * vars->camera.zoom) / 2;
	// p->y -= (vars->height * vars->camera.zoom) / 2;
	
	// Apply rotations
	if (vars->camera.alpha != 0)
	{
		float y_temp = p->y;
		p->y = p->y * cos(vars->camera.alpha) + z * vars->camera.z_scale * sin(vars->camera.alpha);
		z = -y_temp * sin(vars->camera.alpha) + z * cos(vars->camera.alpha);
	}
	if (vars->camera.beta != 0)
	{
		float x_temp = p->x;
		p->x = p->x * cos(vars->camera.beta) + z * vars->camera.z_scale * sin(vars->camera.beta);
		z = -x_temp * sin(vars->camera.beta) + z * cos(vars->camera.beta);
	}
	if (vars->camera.gamma != 0)
	{
		float x_temp = p->x;
		p->x = p->x * cos(vars->camera.gamma) - p->y * sin(vars->camera.gamma);
		p->y = x_temp * sin(vars->camera.gamma) + p->y * cos(vars->camera.gamma);
	}
	
	// Apply projection specific transformations
	if (vars->camera.projection == ISOMETRIC)
	{
		float x_temp = p->x;
		p->x = (x_temp - p->y) * cos(0.523599);
		p->y = (x_temp + p->y) * sin(0.523599) - z * vars->camera.z_scale;
	}
	else if (vars->camera.projection == TOP_VIEW)
	{
		// For top view, we primarily rely on the -90° alpha rotation (already applied)
		// Just apply a slight adjustment to z to maintain some height perspective
		p->y -= z * (vars->camera.z_scale * 0.1); // Subtle height indication
	}
	
	// Apply offsets
	p->x += vars->camera.x_offset;
	p->y += vars->camera.y_offset;
}

// Find min and max z values in the map
void	find_z_range(t_vars *vars, int *min_z, int *max_z)
{
	*min_z = INT_MAX;
	*max_z = INT_MIN;
	
	for (int y = 0; y < vars->height; y++)
	{
		for (int x = 0; x < vars->width; x++)
		{
			if (vars->points[y][x].z < *min_z)
				*min_z = vars->points[y][x].z;
			if (vars->points[y][x].z > *max_z)
				*max_z = vars->points[y][x].z;
		}
	}
}

// Updated draw_map to use the camera settings
void	draw_map(t_vars *vars)
{
	t_point p1, p2;
	int min_z, max_z;
	
	// Find z range for color mapping
	find_z_range(vars, &min_z, &max_z);
	
	// Clear the window
	mlx_clear_window(vars->mlx, vars->win);
	
	for (int y = 0; y < vars->height; y++)
	{
		for (int x = 0; x < vars->width; x++)
		{
			// Initialize point with z and color
			p1.z = vars->points[y][x].z;
			
			// Use height-based color in top view for better visualization
			if (vars->camera.projection == TOP_VIEW && vars->points[y][x].color == C_TEXT)
                p1.color = C_TEXT;
            else
                p1.color = vars->points[y][x].color;
			
			// Apply transformations
			transform_point(vars, &p1, x, y);
			
			// Draw connection to the right
			if (x + 1 < vars->width)
			{
				p2.z = vars->points[y][x + 1].z;
				
				if (vars->camera.projection == TOP_VIEW && vars->points[y][x + 1].color == C_TEXT)
					p2.color = C_TEXT;
				else
					p2.color = vars->points[y][x + 1].color;
					
				transform_point(vars, &p2, x + 1, y);
				bresenham(vars, p1, p2);
			}
			
			// Draw connection downward
			if (y + 1 < vars->height)
			{
				p2.z = vars->points[y + 1][x].z;
				
				if (vars->camera.projection == TOP_VIEW && vars->points[y + 1][x].color == C_TEXT)
					p2.color = C_TEXT;
				else
					p2.color = vars->points[y + 1][x].color;
					
				transform_point(vars, &p2, x, y + 1);
				bresenham(vars, p1, p2);
			}
		}
	}
}

// Draw information panel
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
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Projection: I (isometric) / T (top view)");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Reset: R");
	mlx_string_put(mlx, win, 10, y += 20, C_TEXT, "Exit: ESC");
}
