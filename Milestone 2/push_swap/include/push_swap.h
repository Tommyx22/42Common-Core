/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:36:21 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// Utility
t_stack	*create_stack_element(int value);
void	add_element_bottom(t_stack **stack, t_stack *new);
void	free_stack(t_stack **stack);
int		get_stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);

// Ranking
int		find_min(t_stack *stack);
int		find_max(t_stack *stack);
int		find_position(t_stack *stack, int value);
void	assign_ranks(t_stack **stack);
int		find_target_pos(t_stack *stack_a, int value);

// Moves
void	sa(t_stack **stack_a, int print);
void	sb(t_stack **stack_b, int print);
void	ss(t_stack **stack_a, t_stack **stack_b, int print);
void	pa(t_stack **stack_a, t_stack **stack_b, int print);
void	pb(t_stack **stack_a, t_stack **stack_b, int print);
void	ra(t_stack **stack_a, int print);
void	rb(t_stack **stack_b, int print);
void	rr(t_stack **stack_a, t_stack **stack_b, int print);
void	rra(t_stack **stack_a, int print);
void	rrb(t_stack **stack_b, int print);
void	rrr(t_stack **stack_a, t_stack **stack_b, int print);

// cost moves
void	get_cost_a(int *cost_a, int *target_pos, int size_b, int size_a);
void	get_cost_b(int *cost_b, int size_b);
void	calculate_cost(t_stack *stack_a, t_stack *stack_b,
			int *cost_a, int *cost_b);
int		find_cheapest_move(int *cost_a, int *cost_b, int size_b);
void	push_to_b_helper(t_stack **stack_a, t_stack **stack_b,
			int chunk, int *pushed);
void	push_to_b(t_stack **stack_a, t_stack **stack_b,
			int size, int chunks);
void	process_stack_b_element(t_stack **stack_a, t_stack **stack_b);
int		determine_elements_to_keep(int size);

// sort
void	sort_stack(t_stack **stack_a, t_stack **stack_b);
void	execute_move(t_stack **stack_a, t_stack **stack_b,
			int cost_a, int cost_b);

// check
int		check_duplicates(t_stack *stack, int value);
int		execute_instruction(t_stack **stack_a, t_stack **stack_b,
			char *instr);

// parsing
t_stack	*parse_arguments(int ac, char **av);
t_stack	*parse_single_arg(char *arg);

#endif
