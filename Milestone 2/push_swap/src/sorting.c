/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:26:18 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:30:43 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_stack **stack_a)
{
	int	top;
	int	middle;
	int	bottom;

	if (get_stack_size(*stack_a) != 3)
		return ;
	top = (*stack_a)->value;
	middle = (*stack_a)->next->value;
	bottom = (*stack_a)->next->next->value;
	if (top > middle && middle < bottom && top < bottom)
		sa(stack_a, 1);
	else if (top > middle && middle > bottom)
	{
		sa(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (top > middle && middle < bottom && top > bottom)
		ra(stack_a, 1);
	else if (top < middle && middle > bottom && top < bottom)
	{
		sa(stack_a, 1);
		ra(stack_a, 1);
	}
	else if (top < middle && middle > bottom && top > bottom)
		rra(stack_a, 1);
}

static void	final_sort(t_stack **stack_a)
{
	int	min_pos;
	int	size;

	size = get_stack_size(*stack_a);
	min_pos = find_position(*stack_a, find_min(*stack_a));
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(stack_a, 1);
	}
	else
	{
		while (min_pos++ < size)
			rra(stack_a, 1);
	}
}

static void	sort_small_stack(t_stack **stack_a)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if (size == 3)
		sort_three(stack_a);
}

static void	sort_large_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	elements_to_keep;

	size = get_stack_size(*stack_a);
	elements_to_keep = determine_elements_to_keep(size);
	push_to_b(stack_a, stack_b, size, elements_to_keep);
	if (get_stack_size(*stack_a) == 3)
		sort_three(stack_a);
	while (*stack_b)
		process_stack_b_element(stack_a, stack_b);
	final_sort(stack_a);
}

void	sort_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	if (!stack_a || !*stack_a || is_sorted(*stack_a))
		return ;
	size = get_stack_size(*stack_a);
	assign_ranks(stack_a);
	if (size <= 3)
		sort_small_stack(stack_a);
	else
		sort_large_stack(stack_a, stack_b);
}
