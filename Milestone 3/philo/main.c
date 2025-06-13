/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:53:02 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/13 16:54:13 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	single_philo_exec(t_table *table)
{
	long	start;

	start = get_time();
	printf("%ld 1 has taken a fork\n", get_time() - start);
	usleep(table->time_to_die * 1000);
	printf("%ld 1 died\n", get_time() - start);
	pthread_mutex_lock(&table->end_mtx);
	table->end = true;
	pthread_mutex_unlock(&table->end_mtx);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse(&table, av);
		init(&table);
		if (table.philo_number == 1)
			single_philo_exec(&table);
		else
			start_sim(&table);
		free_all(&table);
	}
	else
	{
		exit_error("Wrong input: \n"
			"try something like ./philo 5 800 200 200 [5]");
	}
	return (0);
}
