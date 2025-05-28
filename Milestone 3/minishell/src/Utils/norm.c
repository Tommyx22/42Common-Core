/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:16:25 by tolanini          #+#    #+#             */
/*   Updated: 2025/05/26 15:33:20 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_variable_in_export(t_shell *shell,
	const char **arg, char **key, char **value)
{
	char	*dollar_env;
	char	*expandible;

	*key = ft_strdup(*arg);
	*value = NULL;
	dollar_env = ft_strjoin("$", *key);
	expandible = in_env(shell, dollar_env, shell->envp);
	if (!expandible)
		*value = ft_strdup("");
	free(dollar_env);
	free(expandible);
}

void	iter_str(int *j, int *k)
{
	(*j)++;
	(*k)++;
}

char	*check_return(char *result)
{
	if (result[0] == '\0')
		return (free(result), NULL);
	return (result);
}
