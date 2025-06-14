/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/13 17:27:46 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1500);
	while (1)
	{
		pthread_mutex_lock(&philo->table->end_mtx);
		if (philo->table->end)
		{
			pthread_mutex_unlock(&philo->table->end_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->table->end_mtx);
		philo_routine_utils(philo);
		if (philo->table->limit_of_meals > 0
			&& philo->meal_count >= philo->table->limit_of_meals)
			break ;
		safe_printf("is sleeping\n", philo);
		smart_sleep(philo->table->time_to_sleep, philo->table);
		safe_printf("is thinking\n", philo);
	}
	return (NULL);
}

static int	monitor_utils(t_table *table, int i, long now, int *full_count)
{
	pthread_mutex_lock(&table->philos[i].meal_mtx);
	if (table->limit_of_meals > 0
		&& table->philos[i].meal_count >= table->limit_of_meals)
		(*full_count)++;
	else if (now - table->philos[i].last_meal_time > table->time_to_die)
	{
		safe_printf("died\n", &table->philos[i]);
		pthread_mutex_lock(&table->end_mtx);
		table->end = true;
		pthread_mutex_unlock(&table->end_mtx);
		pthread_mutex_unlock(&table->philos[i].meal_mtx);
		return (1);
	}
	pthread_mutex_unlock(&table->philos[i].meal_mtx);
	return (0);
}

void	monitor_init(int *full_count, bool *should_exit,
	long *now, t_table *table)
{
	*full_count = 0;
	*now = get_time();
	pthread_mutex_lock(&table->end_mtx);
	*should_exit = table->end;
	pthread_mutex_unlock(&table->end_mtx);
}

void	*monitor(void *arg)
{
	t_table *const	table = (t_table *)arg;
	int				i;
	long			now;
	int				full_count;
	bool			should_exit;

	while (1)
	{
		monitor_init(&full_count, &should_exit, &now, table);
		if (should_exit)
			break ;
		i = -1;
		while (++i < table->philo_number)
			if (monitor_utils(table, i, now, &full_count))
				return (NULL);
		if (full_count == table->philo_number)
		{
			pthread_mutex_lock(&table->end_mtx);
			table->end = true;
			pthread_mutex_unlock(&table->end_mtx);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_sim(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	table->start_time = get_time();
	while (i < table->philo_number)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philo_routine, &table->philos[i]) != 0)
			exit_error("Thread creation failed");
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		exit_error("Monitor thread creation failed");
	i = 0;
	while (i < table->philo_number)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
