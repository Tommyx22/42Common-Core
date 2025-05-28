/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:13:11 by tolanini          #+#    #+#             */
/*   Updated: 2025/05/22 22:38:33 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

static void	clean_and_exit(t_shell *shell, int status)
{
	free_all(shell, 0);
	close(3);
	close(4);
	exit(status);
}

void	ft_exit(t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	write(1, "exit\n", 5);
	if (!shell || !shell->argv)
		clean_and_exit(shell, 0);
	if (shell->argc == 1)
		clean_and_exit(shell, 0);
	if (shell->argc > 1 && !is_valid_number(shell->argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		if (shell->argv[1])
			write(2, shell->argv[1], ft_strlen(shell->argv[1]));
		write(2, ": numeric argument required\n", 28);
		clean_and_exit(shell, 2);
	}
	if (shell->argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit_error(shell, 1);
		return ((void)close(3), (void)close(4));
	}
	if (shell->argc == 2)
		exit_status = (ft_atol(shell->argv[1]) % 256 + 256) % 256;
	clean_and_exit(shell, exit_status);
}
