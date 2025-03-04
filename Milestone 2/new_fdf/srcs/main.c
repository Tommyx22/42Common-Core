/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:56:54 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/04 17:39:43 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	extension_check(char **av)
{
	int		l;
	int		i;
	char	*str;

	l = 0;
	i = 3;
	str = ".fdf";
	while (av[1][l] != '\0')
	{
		l++;
	}
	l--;
	while (i >= 0)
	{
		if (av[1][l] != str[i])
		{
			return (0);
		}
		l--;
		i--;
	}
	return (1);
}

int	close_s(t_vars *vars)
{
	exit(0);
	return (0);
}

static int	key_handle(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		close_s(NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	
	if (ac != 2 || !extension_check(av))
	{
		write(1, "Wrong usage.\n", 14);
		return (0);
	}
	vars = ft_calloc(1, sizeof(t_vars));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	mlx_key_hook(vars->win, key_handle, vars);
	mlx_hook(vars->win, 17, 0, close_s, vars);
	mlx_loop(vars->mlx);
}
