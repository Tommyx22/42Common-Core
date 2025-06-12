/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:52:46 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/12 18:34:58 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork_mutex;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long		last_meal_time;
	t_mtx		meal_mtx;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

struct s_table
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_of_meals;
	long	start_time;
	bool	end;
	t_mtx	end_mtx;
	t_mtx	msg;
	t_fork	*forks;
	t_philo	*philos;
};

// utils
void	exit_error(const char *msg);

// parse
void	parse(t_table *table, char **av);

// init
void	init(t_table *table);

// exec
void	start_sim(t_table *table);

// free
void	free_all(t_table *table);

// time function
long	get_time(void);