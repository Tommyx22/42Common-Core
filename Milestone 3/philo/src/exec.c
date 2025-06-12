/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:20 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/12 18:46:28 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	safe_printf(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end_mtx);
	if (philo->table->end == true)
	{
		pthread_mutex_unlock(&philo->table->end_mtx);
		return ;
	}
	pthread_mutex_lock(&philo->table->msg);
	printf("%ld %d %s",
		(get_time() - philo->table->start_time) / 1000, philo->id, str);
	pthread_mutex_unlock(&philo->table->msg);
	pthread_mutex_unlock(&philo->table->end_mtx);
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->table->end_mtx);
	while (!philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->end_mtx);
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		safe_printf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		safe_printf("has taken a fork\n", philo);
		safe_printf("is eating\n", philo);
		pthread_mutex_lock(&philo->meal_mtx);
		philo->last_meal_time = get_time();
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_mtx);
		usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		safe_printf("is sleeping\n", philo);
		usleep(philo->table->time_to_sleep);
		safe_printf("is thinking\n", philo);
		pthread_mutex_lock(&philo->table->end_mtx);
		if (philo->table->limit_of_meals > 0
			&& philo->meal_count >= philo->table->limit_of_meals)
			break ;
	}
	pthread_mutex_unlock(&philo->table->end_mtx);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table *const	table = (t_table *)arg;
	int				i;
	long			now;
	int				philos_full;

	pthread_mutex_lock(&table->end_mtx);
	while (!table->end)
	{
		pthread_mutex_unlock(&table->end_mtx);
		i = -1;
		philos_full = 0;
		while (++i < table->philo_number)
		{
			now = get_time();
			pthread_mutex_lock(&table->philos[i].meal_mtx);
			if (table->philos[i].meal_count == table->limit_of_meals)
				philos_full++;
			else if ((now - table->philos[i].last_meal_time)
				> table->time_to_die)
			{
				safe_printf("died\n", &table->philos[i]);
				pthread_mutex_lock(&table->end_mtx);
				table->end = true;
				pthread_mutex_unlock(&table->end_mtx);
				pthread_mutex_unlock(&table->philos[i].meal_mtx);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].meal_mtx);
		}
		usleep(1000);
		if (table->philo_number == philos_full)
			return (NULL);
		pthread_mutex_lock(&table->end_mtx);
	}
	pthread_mutex_unlock(&table->end_mtx);
	return (NULL);
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
	i = -1;
	while (++i < table->philo_number)
	{
		if (pthread_create(&table->philos[i].thread_id,
				NULL, philo_routine, &table->philos[i]) != 0)
			exit_error("pthread_create failed");
		usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		exit_error("monitor thread create failed");
	i = -1;
	while (++i < table->philo_number)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(monitor_thread, NULL);
}
