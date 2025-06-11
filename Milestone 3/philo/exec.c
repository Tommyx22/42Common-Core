/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/11 23:35:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	*philo = (t_philo *)arg;
	while (!philo->table->end)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		printf("%ld %d has taken a fork\n", get_time() - philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		printf("%ld %d has taken a fork\n", get_time() - philo->table->start_time, philo->id);
		printf("%ld %d is eating\n", get_time() - philo->table->start_time, philo->id);
		philo->last_meal_time = get_time();
		usleep(philo->table->time_to_eat);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		printf("%ld %d is sleeping\n", get_time() - philo->table->start_time, philo->id);
		usleep(philo->table->time_to_sleep);
		printf("%ld %d is thinking\n", get_time() - philo->table->start_time, philo->id);
		if (philo->table->limit_of_meals > 0 && philo->meal_count >= philo->table->limit_of_meals)
			break;
	}
	return ();
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;
	long	now;

	table = (t_table *)arg;
	while (!table->end)
	{
		i = -1;
		while (++i < table->philo_number)
		{
			now = get_time();
			if ((now - table->philos[i].last_meal_time) > table->time_to_die)
			{
				printf("%ld %d died\n", now - table->start_time, table->philos[i].id);
				table->end = true;
				return ();
			}
		}
		usleep(1000);
	}
	return ();
}

void	start_sim(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (table->limit_of_meals == 0)
		return ;

	table->start_time = get_time();

	i = -1;
	while (++i < table->philo_number)
		table->philos[i].last_meal_time = table->start_time;

	// Avvia i filosofi
	i = -1;
	while (++i < table->philo_number)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]) != 0)
			exit_error("pthread_create failed");
		usleep(100); // leggero delay
	}

	// Avvia il monitor
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		exit_error("monitor thread create failed");

	// Attendi la fine dei filosofi
	i = -1;
	while (++i < table->philo_number)
		pthread_join(table->philos[i].thread_id, NULL);

	// Attendi il monitor
	pthread_join(monitor_thread, NULL);
}
