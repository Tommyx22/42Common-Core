/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:26:53 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static void	free_av(t_stack	*stack_a)
{
	free_stack(&stack_a);
	print_error();
}

static void	free_all(char	**numbers, t_stack	*stack_a)
{
	ft_free_split(numbers);
	free_stack(&stack_a);
	print_error();
}

t_stack	*parse_single_arg(char *arg)
{
	t_stack	*stack_a;
	t_stack	*new;
	char	**numbers;
	int		value;
	int		i;

	stack_a = NULL;
	numbers = ft_split(arg, ' ');
	if (!numbers)
		print_error();
	i = -1;
	while (numbers[++i])
	{
		if (!is_valid_int(numbers[i]))
			free_all(numbers, stack_a);
		value = ft_atoi(numbers[i]);
		if (check_duplicates(stack_a, value))
			free_all(numbers, stack_a);
		new = create_stack_element(value);
		if (!new)
			free_all(numbers, stack_a);
		add_element_bottom(&stack_a, new);
	}
	ft_free_split(numbers);
	return (stack_a);
}

t_stack	*parse_arguments(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*new;
	int		value;
	int		i;

	stack_a = NULL;
	i = 1;
	if (ac == 2)
		return (parse_single_arg(av[1]));
	while (i < ac)
	{
		if (!is_valid_int(av[i]))
			free_av(stack_a);
		value = ft_atoi(av[i]);
		if (check_duplicates(stack_a, value))
			free_av(stack_a);
		new = create_stack_element(value);
		if (!new)
			free_av(stack_a);
		add_element_bottom(&stack_a, new);
		i++;
	}
	return (stack_a);
}
