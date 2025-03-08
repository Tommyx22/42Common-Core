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

static int	extension_check(char **av)
{
	int		l = 0;
	int		i = 3;
	char	*str = ".fdf";

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
	int		redraw;

	vars = (t_vars *)param;
	redraw = 0;

	if (keycode == KEY_ESC)
		close_s(vars);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS || 
			keycode == KEY_NUM_PLUS || keycode == KEY_NUM_MINUS)
	{
		zoom(keycode, vars);
		redraw = 1;
	}
	else if (keycode == KEY_UP || keycode == KEY_DOWN || 
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		move(keycode, vars);
		redraw = 1;
	}
	else if (keycode == KEY_W || keycode == KEY_S || 
			keycode == KEY_A || keycode == KEY_D || 
			keycode == KEY_Q || keycode == KEY_E)
	{
		rotate(keycode, vars);
		redraw = 1;
	}
	else if (keycode == KEY_I || keycode == KEY_T)
	{
		change_projection(keycode, vars);
		redraw = 1;
	}
	else if (keycode == KEY_PAGE_UP || keycode == KEY_PAGE_DOWN)
	{
		change_z_scale(keycode, vars);
		redraw = 1;
	}
	else if (keycode == KEY_R)
	{
		reset_camera(vars);
		redraw = 1;
	}

	if (redraw)
	{
		draw_map(vars);
		draw_menu(vars);
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	
	if (ac != 2 || !extension_check(av))
	{
		write(1, "Wrong usage.\n", 14);
		return (1);
	}

	vars = ft_calloc(1, sizeof(t_vars));
	if (!vars)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	// Initialize camera defaults before parsing
	init_camera(&vars->camera);

	parse(av, vars);

	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		printf("MLX initialization failed\n");
		close_s(vars);
		return (1);
	}

	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!vars->win)
	{
		printf("Window creation failed\n");
		close_s(vars);
		return (1);
	}

	// Draw initial map and menu
	draw_map(vars);
	draw_menu(vars);

	mlx_key_hook(vars->win, key_handle, vars);
	mlx_hook(vars->win, 17, 0, close_s, vars);
	mlx_loop(vars->mlx);
	
	return (0);
}
