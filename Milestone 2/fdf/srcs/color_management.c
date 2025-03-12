/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:30:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/12 17:33:23 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

static int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

static int	get_b(int color)
{
	return (color & 0xFF);
}

static int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	color_lerp(int c1, int c2, double t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(c1) + (int)(t * (get_r(c2) - get_r(c1)));
	g = get_g(c1) + (int)(t * (get_g(c2) - get_g(c1)));
	b = get_b(c1) + (int)(t * (get_b(c2) - get_b(c1)));
	return (create_rgb(r, g, b));
}
