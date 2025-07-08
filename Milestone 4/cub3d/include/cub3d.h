/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:41:53 by tolanini          #+#    #+#             */
/*   Updated: 2025/07/08 18:57:58 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_vars;

#endif