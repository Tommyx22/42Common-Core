/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:53:19 by tolanini          #+#    #+#             */
/*   Updated: 2025/05/23 00:33:07 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_env_var(t_shell *shell, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, len) == 0
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	execute_path_command(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	**paths;

	if (cmd->command == NULL && cmd->heredoc != NULL)
		return (close(3), close(4), 0);
	path = get_env_var(shell, "PATH");
	if (path != NULL)
		paths = ft_split(path, ':');
	else
		paths = NULL;
	if (cmd->command == NULL || cmd->command[0] == '\0')
	{
		if (paths != NULL)
			ft_free_split(paths);
		close(3);
		close(4);
		return (127);
	}
	return (handle_fork_and_execution(shell, cmd, paths));
}

static int	handle_child_process(t_shell *shell, t_command *cmd)
{
	set_signals_noninteractive();
	handle_heredoc(shell, cmd);
	if (g_signal == SIGINT)
	{
		free_all(shell, 0);
		exit(130);
	}
	handle_redirections(shell, cmd);
	return (execute_path_command(shell, cmd));
}

static int	handle_parent_process_s(pid_t pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_manager);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGPIPE)
			exit_code = 141;
		else
			exit_code = 128 + WTERMSIG(status);
	}
	else
		exit_code = 1;
	return (exit_code);
}

int	execute_command(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = fork();
	if (pid == 0)
	{
		exit_code = handle_child_process(shell, cmd);
		check_signal_error(&exit_code);
		free_all(shell, 0);
		exit(exit_code);
	}
	else if (pid > 0)
	{
		exit_code = handle_parent_process_s(pid);
		exit_error(shell, exit_code);
	}
	else
	{
		perror("fork");
		exit_code = 1;
		exit_error(shell, exit_code);
	}
	return (exit_code);
}
