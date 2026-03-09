/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:48 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack **stack_a, int print)
{
	t_stack	*first;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	first = *stack_a;
	last = *stack_a;
	while (last->next)
		last = last->next;
	*stack_a = first->next;
	first->next = NULL;
	last->next = first;
	if (print)
		ft_putendl_fd("ra", 1);
}

void	rb(t_stack **stack_b, int print)
{
	t_stack	*first;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	first = *stack_b;
	last = *stack_b;
	while (last->next)
		last = last->next;
	*stack_b = first->next;
	first->next = NULL;
	last->next = first;
	if (print)
		ft_putendl_fd("rb", 1);
}

void	rra(t_stack **stack_a, int print)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	last = *stack_a;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
	if (print)
		ft_putendl_fd("rra", 1);
}

void	rrb(t_stack **stack_b, int print)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	last = *stack_b;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
	if (print)
		ft_putendl_fd("rrb", 1);
}
