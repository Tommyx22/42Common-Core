/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_swap_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:38:40 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **stack_a, int print)
{
	t_stack	*temp;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
	if (print)
		ft_putendl_fd("sa", 1);
}

void	sb(t_stack **stack_b, int print)
{
	t_stack	*temp;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
	if (print)
		ft_putendl_fd("sb", 1);
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	if (print)
		ft_putendl_fd("ss", 1);
}

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;

	if (!*stack_b)
		return ;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = *stack_a;
	*stack_a = temp;
	if (print)
		ft_putendl_fd("pa", 1);
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;

	if (!*stack_a)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = *stack_b;
	*stack_b = temp;
	if (print)
		ft_putendl_fd("pb", 1);
}
