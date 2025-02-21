/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:59:49 by tolanini          #+#    #+#             */
/*   Updated: 2025/02/21 17:47:46 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	expose_handle(t_fdf *fdf);

int	extension_check(char **av)
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

int	main(int argc, char **argv)
{
	char	*file_name;
	t_fdf	*fdf;

	if (argc != 2)
	{
		write(1, "Wrong usage. Expected './fdf <file_path>'.\n", 44);
		exit(0);
	}
	if (!extension_check(argv))
	{
		write(1, "Wrong extension of file: expected '.fdf'\n", 42);
		return (0);
	}
	file_name = argv[1];
	fdf = init_fdf(file_name);
	render(fdf);
	mlx_key_hook(fdf->win, &key_handle, fdf);
	mlx_hook(fdf->win, 17, 0, &close_all, fdf);
	mlx_expose_hook(fdf->win, &expose_handle, fdf);
	mlx_loop(fdf->mlx);
}

static int	expose_handle(t_fdf *fdf)
{
	render(fdf);
	return (0);
}
