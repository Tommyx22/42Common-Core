/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_uti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:41:39 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_size(t_stack *stack)
{
	int		size;
	t_stack	*temp;

	size = 0;
	temp = stack;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

int	is_sorted(t_stack *stack)
{
	t_stack	*temp;

	temp = stack;
	while (temp && temp->next)
	{
		if (temp->value > temp->next->value)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_stack	*create_stack_element(int value)
{
	t_stack	*new_element;

	new_element = (t_stack *)malloc(sizeof(t_stack));
	if (!new_element)
		return (NULL);
	new_element->value = value;
	new_element->index = -1;
	new_element->next = NULL;
	return (new_element);
}

void	add_element_bottom(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	free_stack(t_stack **stack)
{
	t_stack	*temp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
	*stack = NULL;
}
