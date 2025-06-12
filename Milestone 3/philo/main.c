/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:53:02 by tolanini          #+#    #+#             */
/*   Updated: 2025/06/11 15:00:24 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table table;
	if (ac == 5 || ac == 6)
	{
		parse(&table, av);
		init(&table);
		start_sim(&table);
		free_all(&table);
	}
	else
	{
		exit_error("Wrong input: \n"
			"try something like ./philo 5 800 200 200 [5]");
	}
}
