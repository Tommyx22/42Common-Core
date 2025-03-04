/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:54:40 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/04 17:51:59 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

# define WINDOW_WIDTH		1200
# define WINDOW_HEIGHT		900
# define C_TEXT				0xffffff
# define KEY_ESC    65307

#endif