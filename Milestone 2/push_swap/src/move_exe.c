/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:44:30 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rr_exe(t_stack **stack_a, t_stack **stack_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(stack_a, stack_b, 1);
		(*cost_a)--;
		(*cost_b)--;
	}
}

static void	rrr_exe(t_stack **stack_a, t_stack **stack_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		rrr(stack_a, stack_b, 1);
		(*cost_a)++;
		(*cost_b)++;
	}
}

void	execute_move(t_stack **stack_a, t_stack **stack_b,
			int cost_a, int cost_b)
{
	rr_exe(stack_a, stack_b, &cost_a, &cost_b);
	rrr_exe(stack_a, stack_b, &cost_a, &cost_b);
	while (cost_a > 0)
	{
		ra(stack_a, 1);
		cost_a--;
	}
	while (cost_a < 0)
	{
		rra(stack_a, 1);
		cost_a++;
	}
	while (cost_b > 0)
	{
		rb(stack_b, 1);
		cost_b--;
	}
	while (cost_b < 0)
	{
		rrb(stack_b, 1);
		cost_b++;
	}
	pa(stack_a, stack_b, 1);
}
