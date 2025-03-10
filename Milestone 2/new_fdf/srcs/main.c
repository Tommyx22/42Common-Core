/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:56:54 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/08 17:47:14 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_s(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		if (vars->points)
		{
			while (i < vars->height)
			{
				free(vars->points[i]);
				i++;
			}
			free(vars->points);
		}
		if (vars->win && vars->mlx)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->mlx)
		{
			mlx_destroy_display(vars->mlx);
			free(vars->mlx);
		}
		free(vars);
	}
	exit(0);
	return (0);
}

void	init_camera(t_cam *camera)
{
	camera->x_offset = OFFSET_X;
	camera->y_offset = OFFSET_Y;
	camera->z_scale = Z_SCALE;
	camera->zoom = SCALE_FACTOR;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0.523599;
	camera->projection = ISOMETRIC;
}

static int	extension_check(char **av)
{
	int		l;
	int		i;
	char	*str;

	l = 0;
	i = 3;
	str = ".fdf";
	while (av[1][l] != '\0')
		l++;
	l--;
	while (i >= 0)
	{
		if (av[1][l] != str[i])
			return (0);
		l--;
		i--;
	}
	return (1);
}

static int	key_handle(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (keycode == KEY_ESC)
		close_s(vars);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS
		|| keycode == KEY_NUM_PLUS || keycode == KEY_NUM_MINUS)
		zoom(keycode, vars);
	else if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		move(keycode, vars);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_Q || keycode == KEY_E)
		rotate(keycode, vars);
	else if (keycode == KEY_I || keycode == KEY_T)
		change_projection(keycode, vars);
	else if (keycode == KEY_PAGE_UP || keycode == KEY_PAGE_DOWN)
		change_z_scale(keycode, vars);
	else if (keycode == KEY_R)
		init_camera(&vars->camera);
	draw_map(vars);
	draw_menu(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	if (ac != 2 || !extension_check(av) || !vars)
		return (write(1, "Wrong usage.\n", 14), 1);
	init_camera(&vars->camera);
	parse(av, vars);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!vars->mlx || !vars->win)
	{
		printf("MLX initialization failed\n");
		close_s(vars);
		return (1);
	}
	draw_map(vars);
	draw_menu(vars);
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_hook(vars->win, 17, 0, close_s, vars);
	mlx_loop(vars->mlx);
	return (0);
}
