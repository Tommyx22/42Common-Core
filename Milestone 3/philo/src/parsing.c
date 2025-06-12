/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:01:05 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/11 13:51:08 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*valid_input(const char *str)
{
	const char	*num;
	int			len;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		exit_error("Wrong input, give me only positive number");
	if (!(*str >= '0' && *str <= '9'))
		exit_error("Incorrect input, not a number");
	num = str;
	while (*str++ >= '0' && *str++ <= '9')
		++len;
	if (len > 10)
		exit_error("Exceeded INT_MAX limit");
	return (num);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		exit_error("Exceeded INT_MAX limit");
	return (num);
}

void	parse(t_table *table, char **av)
{
	table->philo_number = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		exit_error("Error with timestamp us a timestamp major than 60ms");
	if (av[5])
		table->limit_of_meals = ft_atol(av[5]);
	else
		table->limit_of_meals = -1;
}
