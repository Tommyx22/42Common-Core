/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 05:07:44 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_b_helper(t_stack **stack_a, t_stack **stack_b,
	int chunk, int *pushed)
{
	pb(stack_a, stack_b, 1);
	if ((*stack_b)->index <= chunk)
		rb(stack_b, 1);
	(*pushed)++;
}

void	push_to_b(t_stack **stack_a, t_stack **stack_b,
	int size, int chunks)
{
	int	chunk_size;
	int	i;
	int	pushed;
	int	current_chunk;
	int	mid_chunk;

	chunk_size = size / chunks;
	current_chunk = 1;
	pushed = 0;
	while (*stack_a && get_stack_size(*stack_a) > 3)
	{
		i = 0;
		mid_chunk = (current_chunk * chunk_size) - (chunk_size / 2);
		while (i < size && pushed < current_chunk * chunk_size
			&& get_stack_size(*stack_a) > 3)
		{
			if ((*stack_a)->index <= current_chunk * chunk_size)
				push_to_b_helper(stack_a, stack_b, mid_chunk, &pushed);
			else
				ra(stack_a, 1);
			i++;
		}
		current_chunk++;
	}
}

int	determine_elements_to_keep(int size)
{
	if (size <= 100)
		return (3);
	else
		return (7);
}

void	process_stack_b_element(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_b_size;
	int	*cost_a;
	int	*cost_b;
	int	cheapest_pos;

	stack_b_size = get_stack_size(*stack_b);
	cost_a = (int *)malloc(sizeof(int) * stack_b_size);
	cost_b = (int *)malloc(sizeof(int) * stack_b_size);
	if (!cost_a || !cost_b)
	{
		if (cost_a)
			free(cost_a);
		if (cost_b)
			free(cost_b);
		return ;
	}
	calculate_cost(*stack_a, *stack_b, cost_a, cost_b);
	cheapest_pos = find_cheapest_move(cost_a, cost_b, stack_b_size);
	execute_move(stack_a, stack_b, cost_a[cheapest_pos], cost_b[cheapest_pos]);
	free(cost_a);
	free(cost_b);
}
