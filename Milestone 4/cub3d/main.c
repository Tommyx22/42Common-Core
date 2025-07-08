/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/08 19:22:08 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	key_handle(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (keycode == )

	else if (keycode == )

	else if (keycode == )

    else if (keycode == )
        
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	if (ac != 2 || !vars)
		return (write(1, "Error.\n", 14), 1);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!vars->mlx || !vars->win)
	{
		printf("MLX initialization failed\n");
		close_s(vars);
		return (1);
	}
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_loop(vars->mlx);
	return (0);
}