/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:18:31 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_position_for_edge_case(t_stack *stack_a, int value)
{
	int	min;
	int	max;

	min = find_min(stack_a);
	max = find_max(stack_a);
	if (value < min || value > max)
		return (find_position(stack_a, min));
	return (-1);
}

static int	find_closest_larger_position(t_stack *stack_a, int value)
{
	int		closest_bigger;
	int		target_pos;
	int		pos;
	t_stack	*temp;

	closest_bigger = INT_MAX;
	target_pos = 0;
	pos = 0;
	temp = stack_a;
	while (temp)
	{
		if (temp->value > value && temp->value < closest_bigger)
		{
			closest_bigger = temp->value;
			target_pos = pos;
		}
		temp = temp->next;
		pos++;
	}
	return (target_pos);
}

int	find_target_pos(t_stack *stack_a, int value)
{
	int	edge_pos;

	edge_pos = find_position_for_edge_case(stack_a, value);
	if (edge_pos != -1)
		return (edge_pos);
	return (find_closest_larger_position(stack_a, value));
}
