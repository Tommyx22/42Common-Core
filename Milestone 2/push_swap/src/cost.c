/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:00:19 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_cost_a(int *cost_a, int *target_pos, int size_b, int size_a)
{
	int	i;
	int	pos;

	i = 0;
	while (i < size_b)
	{
		pos = target_pos[i];
		cost_a[i] = pos;
		if (pos > size_a / 2)
			cost_a[i] = -(size_a - pos);
		i++;
	}
}

void	get_cost_b(int *cost_b, int size_b)
{
	int	i;

	i = 0;
	while (i < size_b)
	{
		cost_b[i] = i;
		if (i > size_b / 2)
			cost_b[i] = -(size_b - i);
		i++;
	}
}

void	calculate_cost(t_stack *stack_a, t_stack *stack_b,
	int *cost_a, int *cost_b)
{
	int		size_a;
	int		size_b;
	int		i;
	int		*target_pos;
	t_stack	*temp_b;

	size_a = get_stack_size(stack_a);
	size_b = get_stack_size(stack_b);
	target_pos = malloc(sizeof(int) * (size_b + 1));
	if (!target_pos)
		return ;
	i = 0;
	temp_b = stack_b;
	while (temp_b)
	{
		target_pos[i] = find_target_pos(stack_a, temp_b->value);
		temp_b = temp_b->next;
		i++;
	}
	target_pos[i] = -1;
	get_cost_b(cost_b, size_b);
	get_cost_a(cost_a, target_pos, size_b, size_a);
	free(target_pos);
}

static int	get_cost(int cost_a, int cost_b)
{
	int	cost;

	if (cost_a >= 0 && cost_b >= 0)
	{
		if (cost_a > cost_b)
			cost = cost_a;
		else
			cost = cost_b;
	}
	else if (cost_a <= 0 && cost_b <= 0)
	{
		if (ft_absolute_value(cost_a) > ft_absolute_value(cost_b))
			cost = ft_absolute_value(cost_a);
		else
			cost = ft_absolute_value(cost_b);
	}
	else
		cost = ft_absolute_value(cost_a) + ft_absolute_value(cost_b);
	return (cost);
}

int	find_cheapest_move(int *cost_a, int *cost_b, int size_b)
{
	int	i;
	int	cheapest;
	int	cheapest_pos;
	int	cost;

	cheapest = INT_MAX;
	cheapest_pos = 0;
	i = 0;
	while (i < size_b)
	{
		cost = get_cost(cost_a[i], cost_b[i]);
		if (cost < cheapest)
		{
			cheapest = cost;
			cheapest_pos = i;
		}
		i++;
	}
	return (cheapest_pos);
}
