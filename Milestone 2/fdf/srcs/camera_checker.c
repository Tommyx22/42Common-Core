/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:07:18 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/12 17:17:01 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	angle_checker(t_vars *vars, t_point *p, float z)
{
	float	y_temp;
	float	x_temp;

	if (vars->camera.alpha != 0)
	{
		y_temp = p->y;
		p->y = p->y * cos(vars->camera.alpha) + z
			* vars->camera.z_scale * sin(vars->camera.alpha);
		z = -y_temp * sin(vars->camera.alpha) + z * cos(vars->camera.alpha);
	}
	if (vars->camera.beta != 0)
	{
		x_temp = p->x;
		p->x = p->x * cos(vars->camera.beta) + z
			* vars->camera.z_scale * sin(vars->camera.beta);
		z = -x_temp * sin(vars->camera.beta) + z
			* cos(vars->camera.beta);
	}
	if (vars->camera.gamma != 0)
	{
		x_temp = p->x;
		p->x = p->x * cos(vars->camera.gamma) - p->y * sin(vars->camera.gamma);
		p->y = x_temp * sin(vars->camera.gamma) + p->y
			* cos(vars->camera.gamma);
	}
}

void	check_camera(t_vars *vars, t_point *p, float z)
{
	float	x_temp;

	angle_checker(vars, p, z);
	if (vars->camera.projection == ISOMETRIC)
	{
		x_temp = p->x;
		p->x = (x_temp - p->y) * cos(0.523599);
		p->y = (x_temp + p->y) * sin(0.523599) - z * vars->camera.z_scale;
	}
	else if (vars->camera.projection == TOP_VIEW)
		p->y -= z * (vars->camera.z_scale * 0.1);
}
