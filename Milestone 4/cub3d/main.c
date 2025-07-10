/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/10 16:34:37 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_s(t_vars *vars)
{
	if (vars->win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars);
	exit(0);
	return (0);
}

static int	key_handle(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_clear_window(vars->mlx, vars->win);
	if (keycode == KEY_ESC)
		close_s(vars);
	else if (keycode == KEY_A)
		mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, "A pressed");
	else if (keycode == KEY_S)
		mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, "S pressed");
    else if (keycode == KEY_D)
		mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, "D pressed");
	else if (keycode == KEY_W)
		mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, "W pressed");
	return (0);
}

int	main(int ac, char **av)
{
	(void)av;
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	if (ac != 2 || !vars)
		return (write(1, "Error.\n", 7), 1);
	//prase(av, ecc...);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!vars->mlx || !vars->win)
	{
		printf("MLX initialization failed\n");
		close_s(vars);
		return (1);
	}
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_hook(vars->win, 17, 0, close_s, vars);
	mlx_loop(vars->mlx);
	return (0);
}