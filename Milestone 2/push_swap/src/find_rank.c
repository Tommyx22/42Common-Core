/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:32:15 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(t_stack *stack)
{
	int		min;
	t_stack	*temp;

	if (!stack)
		return (0);
	min = stack->value;
	temp = stack;
	while (temp)
	{
		if (temp->value < min)
			min = temp->value;
		temp = temp->next;
	}
	return (min);
}

int	find_max(t_stack *stack)
{
	int		max;
	t_stack	*temp;

	if (!stack)
		return (0);
	max = stack->value;
	temp = stack;
	while (temp)
	{
		if (temp->value > max)
			max = temp->value;
		temp = temp->next;
	}
	return (max);
}

int	find_position(t_stack *stack, int value)
{
	int		pos;
	t_stack	*temp;

	pos = 0;
	temp = stack;
	while (temp)
	{
		if (temp->value == value)
			return (pos);
		temp = temp->next;
		pos++;
	}
	return (-1);
}
