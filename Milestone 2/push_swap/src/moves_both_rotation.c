/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_both_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:16 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	if (print)
		ft_putendl_fd("rr", 1);
}

void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	if (print)
		ft_putendl_fd("rrr", 1);
}
