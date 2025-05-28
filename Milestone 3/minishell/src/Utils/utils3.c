/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:04:39 by tolanini          #+#    #+#             */
/*   Updated: 2025/05/21 23:12:20 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_count(t_shell *shell, int *i)
{
	if (shell->cmd[(*i) + 2] != '<')
	{
		shell->doc_count++;
		(*i)++;
	}
	else
		while (shell->cmd[*i] == '<')
			(*i)++;
}

void	count_heredoc(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell-> cmd && shell->cmd[i])
	{
		if (shell->cmd[i] == 34 || shell->cmd[i] == 39)
		{
			i++;
			while (shell->cmd[i] && shell->cmd[i] != 34 && shell->cmd[i] != 39)
				i++;
		}
		if (shell->cmd[i] == '<' && shell->cmd[i + 1]
			&& shell->cmd[i + 1] == '<')
			add_count(shell, &i);
		if (shell->cmd[i])
			i++;
	}
	if (shell->doc_count)
		shell->heredoc = ft_calloc((shell->doc_count + 1), sizeof(char *));
}

static void	add_count_pipe(t_shell *shell, t_command *command, int *i)
{
	if (shell->cmd[(*i) + 2] != '<')
	{
		command->doc_count++;
		(*i)++;
	}
	else
		while (shell->cmd[*i] == '<')
			(*i)++;
}

void	count_heredoc_pipe(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	while (shell->cmd && shell->cmd[i])
	{
		if (shell->cmd[i] == 34 || shell->cmd[i] == 39)
		{
			i++;
			while (shell->cmd[i] && shell->cmd[i] != 34 && shell->cmd[i] != 39)
				i++;
		}
		if (shell->cmd[i] == '<' && shell->cmd[i + 1]
			&& shell->cmd[i + 1] == '<')
			add_count_pipe(shell, command, &i);
		if (shell->cmd[i])
			i++;
	}
	if (command->doc_count)
		command->heredoc = ft_calloc(command->doc_count + 1, sizeof(char *));
}

int	only_quotes(char *str)
{
	if (str[0] && (str[0] == 34 || str[0] == 39) && str[1]
		&& (str[1] == 34 || str[1] == 39) && !str[2])
		return (0);
	return (1);
}
