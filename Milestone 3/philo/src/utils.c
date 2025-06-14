/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:55:18 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/13 15:45:00 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
	{
		i = -1;
		while (++i < table->philo_number)
			pthread_mutex_destroy(&table->philos[i].meal_mtx);
		free(table->philos);
	}
	pthread_mutex_destroy(&table->end_mtx);
	pthread_mutex_destroy(&table->msg);
}

void	safe_printf(char *str, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->table->end_mtx);
	if (philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->end_mtx);
		return ;
	}
	current_time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->msg);
	printf("%ld %d %s", current_time, philo->id, str);
	pthread_mutex_unlock(&philo->table->msg);
	pthread_mutex_unlock(&philo->table->end_mtx);
}

void	smart_sleep(long ms, t_table *table)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		usleep(100);
		pthread_mutex_lock(&table->end_mtx);
		if (table->end)
		{
			pthread_mutex_unlock(&table->end_mtx);
			break ;
		}
		pthread_mutex_unlock(&table->end_mtx);
	}
}
