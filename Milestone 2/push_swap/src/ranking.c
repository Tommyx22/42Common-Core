/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:34:54 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reset_indexes(t_stack **stack)
{
	t_stack	*current;

	current = *stack;
	while (current)
	{
		current->index = -1;
		current = current->next;
	}
}

static t_stack	*find_smallest_unranked(t_stack **stack)
{
	t_stack	*current;
	t_stack	*smallest;
	int		min;

	current = *stack;
	smallest = NULL;
	min = INT_MAX;
	while (current)
	{
		if (current->index == -1 && current->value < min)
		{
			smallest = current;
			min = current->value;
		}
		current = current->next;
	}
	return (smallest);
}

void	assign_ranks(t_stack **stack)
{
	int		rank;
	int		size;
	t_stack	*smallest;

	rank = 1;
	size = get_stack_size(*stack);
	reset_indexes(stack);
	while (rank <= size)
	{
		smallest = find_smallest_unranked(stack);
		if (smallest != NULL)
			smallest->index = rank++;
	}
}
