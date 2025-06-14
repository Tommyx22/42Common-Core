/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:46:37 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/14 14:46:51 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine_utils(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	safe_printf("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	safe_printf("has taken a fork\n", philo);
	safe_printf("is eating\n", philo);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mtx);
	smart_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}
