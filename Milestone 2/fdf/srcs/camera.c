/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:30:12 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/08 17:52:59 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	zoom(int key, t_vars *vars)
{
	if (key == KEY_PLUS || key == KEY_NUM_PLUS)
	{
		vars->camera.zoom += 0.5;
	}
	else if (key == KEY_MINUS || key == KEY_NUM_MINUS)
	{
		vars->camera.zoom -= 0.5;
		if (vars->camera.zoom < 0.1)
			vars->camera.zoom = 0.1;
	}
}

void	move(int key, t_vars *vars)
{
	if (key == KEY_UP)
		vars->camera.y_offset -= 10;
	else if (key == KEY_DOWN)
		vars->camera.y_offset += 10;
	else if (key == KEY_LEFT)
		vars->camera.x_offset -= 10;
	else if (key == KEY_RIGHT)
		vars->camera.x_offset += 10;
}

void	rotate(int key, t_vars *vars)
{
	if (key == KEY_W)
		vars->camera.alpha += 0.05;
	else if (key == KEY_S)
		vars->camera.alpha -= 0.05;
	else if (key == KEY_A)
		vars->camera.beta -= 0.05;
	else if (key == KEY_D)
		vars->camera.beta += 0.05;
	else if (key == KEY_Q)
		vars->camera.gamma += 0.05;
	else if (key == KEY_E)
		vars->camera.gamma -= 0.05;
}

void	change_projection(int key, t_vars *vars)
{
	if (key == KEY_I)
	{
		vars->camera.projection = ISOMETRIC;
		init_camera(&vars->camera);
	}
	else if (key == KEY_T)
	{
		vars->camera.projection = TOP_VIEW;
		vars->camera.alpha = M_PI / 2;
		vars->camera.beta = 0;
		vars->camera.gamma = 0;
		vars->camera.z_scale = Z_SCALE / 2;
		vars->camera.x_offset = OFFSET_X;
		vars->camera.y_offset = OFFSET_Y;
	}
}

void	change_z_scale(int key, t_vars *vars)
{
	if (key == KEY_PAGE_UP)
	{
		vars->camera.z_scale += 1;
		if (vars->camera.z_scale > 50)
			vars->camera.z_scale = 50;
	}
	else if (key == KEY_PAGE_DOWN)
	{
		vars->camera.z_scale -= 1;
		if (vars->camera.z_scale < 1)
			vars->camera.z_scale = 1;
	}
}
