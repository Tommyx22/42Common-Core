/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:35 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/12 17:56:56 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_bresenham(t_point p1, t_point p2, t_bres *b)
{
	b->dx = abs(p2.x - p1.x);
	b->dy = -abs(p2.y - p1.y);
	b->err = b->dx + b->dy;
	b->dist = sqrt(b->dx * b->dx + (-b->dy) * (-b->dy));
	b->step = 0;
	b->current = p1;
	if (p1.x < p2.x)
		b->sx = 1;
	else
		b->sx = -1;
	if (p1.y < p2.y)
		b->sy = 1;
	else
		b->sy = -1;
}

void	update_bresenham(t_bres *b)
{
	b->e2 = 2 * b->err;
	if (b->e2 >= b->dy)
	{
		if (b->current.x == b->p2.x)
			return ;
		b->err += b->dy;
		b->current.x += b->sx;
	}
	if (b->e2 <= b->dx)
	{
		if (b->current.y == b->p2.y)
			return ;
		b->err += b->dx;
		b->current.y += b->sy;
	}
	b->step += 1.0;
}
