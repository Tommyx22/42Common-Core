/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:55:18 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/01 16:02:04 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_all(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = -1;
		while (++i < table->philo_number)
			pthread_mutex_destroy(&table->forks[i].fork_mutex);
		free(table->forks);
	}
	if (table->philos)
		free(table->philos);
}
