/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_uti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:46:57 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_valid_instruction(char *instr)
{
	if (ft_strncmp(instr, "sa\n", 3) == 0
		|| ft_strncmp(instr, "sb\n", 3) == 0
		|| ft_strncmp(instr, "ss\n", 3) == 0
		|| ft_strncmp(instr, "pa\n", 3) == 0
		|| ft_strncmp(instr, "pb\n", 3) == 0
		|| ft_strncmp(instr, "ra\n", 3) == 0
		|| ft_strncmp(instr, "rb\n", 3) == 0
		|| ft_strncmp(instr, "rr\n", 3) == 0
		|| ft_strncmp(instr, "rra\n", 4) == 0
		|| ft_strncmp(instr, "rrb\n", 4) == 0
		|| ft_strncmp(instr, "rrr\n", 4) == 0)
		return (1);
	return (0);
}

static void	execute_stack_operation(t_stack **stack_a,
	t_stack **stack_b, char *instr)
{
	if (ft_strncmp(instr, "sa\n", 3) == 0)
		sa(stack_a, 0);
	else if (ft_strncmp(instr, "sb\n", 3) == 0)
		sb(stack_b, 0);
	else if (ft_strncmp(instr, "ss\n", 3) == 0)
		ss(stack_a, stack_b, 0);
	else if (ft_strncmp(instr, "pa\n", 3) == 0)
		pa(stack_a, stack_b, 0);
	else if (ft_strncmp(instr, "pb\n", 3) == 0)
		pb(stack_a, stack_b, 0);
	else if (ft_strncmp(instr, "ra\n", 3) == 0)
		ra(stack_a, 0);
	else if (ft_strncmp(instr, "rb\n", 3) == 0)
		rb(stack_b, 0);
	else if (ft_strncmp(instr, "rr\n", 3) == 0)
		rr(stack_a, stack_b, 0);
	else if (ft_strncmp(instr, "rra\n", 4) == 0)
		rra(stack_a, 0);
	else if (ft_strncmp(instr, "rrb\n", 4) == 0)
		rrb(stack_b, 0);
	else if (ft_strncmp(instr, "rrr\n", 4) == 0)
		rrr(stack_a, stack_b, 0);
}

int	execute_instruction(t_stack **stack_a, t_stack **stack_b, char *instr)
{
	int	result;

	if (!is_valid_instruction(instr))
		return (0);
	execute_stack_operation(stack_a, stack_b, instr);
	result = 1;
	return (result);
}
