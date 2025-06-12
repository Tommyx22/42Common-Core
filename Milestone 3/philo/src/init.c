/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:28:42 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/12 18:35:25 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meal_count = 0;
		philo->table = table;
		philo->left_fork = &table->forks[(i + 1) % table->philo_number];
		philo->right_fork = &table->forks[i];
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &table->forks[i];
			philo->right_fork = &table->forks[(i + 1) % table->philo_number];
		}
	}
}

void	init(t_table *table)
{
	int	i;

	i = -1;
	table->end = false;
	if (pthread_mutex_init(&table->end_mtx, NULL))
		exit_error("mutex init failed");
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (table->philos == NULL)
		exit_error("error with malloc");
	table->forks = malloc(sizeof(t_fork) * table->philo_number);
	if (table->forks == NULL)
		exit_error("error with malloc");
	while (++i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i].fork_mutex, NULL))
			exit_error("mutex init failed");
		if (pthread_mutex_init(&table->philos[i].meal_mtx, NULL))
			exit_error("mutex init failed");
		table->forks[i].fork_id = i;
	}
	if (pthread_mutex_init(&table->msg, NULL))
		exit_error("mutex init failed");
	philo_init(table);
}
