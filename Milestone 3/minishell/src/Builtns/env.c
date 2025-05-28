/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:36:04 by tolanini          #+#    #+#             */
/*   Updated: 2025/05/20 21:40:58 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"//cartella builtins

int	env(char **envp)
{
	int		i;
	char	*str;

	i = -1;
	while (envp[++i])
	{
		str = strrchr(envp[i], '=');
		if (str && str[1])
			ft_putendl_fd(envp[i], 1);
	}
	return (1);
}
