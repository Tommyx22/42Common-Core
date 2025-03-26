/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:48:15 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_duplicates(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	read_and_execute_instructions(t_stack **stack_a, t_stack **stack_b)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		ret = execute_instruction(stack_a, stack_b, line);
		free(line);
		if (!ret)
		{
			write(2, "Error\n", 6);
			free_stack(stack_a);
			free_stack(stack_b);
			exit(1);
		}
	}
}

static void	check_result(t_stack **stack_a, t_stack **stack_b)
{
	if (is_sorted(*stack_a) && !*stack_b)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	stack_a = parse_arguments(ac, av);
	stack_b = NULL;
	read_and_execute_instructions(&stack_a, &stack_b);
	check_result(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
