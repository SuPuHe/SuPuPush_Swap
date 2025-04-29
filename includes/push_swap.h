/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:50:51 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 13:55:55 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_stack
{
	long				value;
	struct s_stack		*next;
}	t_stack;

typedef struct s_cost
{
	int		cost_a;
	int		cost_b;
	int		total;
	t_stack	*node;
}	t_cost;

//moves
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a, int helper);
void	rb(t_stack **a, int helper);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a, int helper);
void	rrb(t_stack **a, int helper);
void	rrr(t_stack **a, t_stack **b);
//input cheks
long	ft_long_atoi(const char *string);
t_stack	*create_node(long value);
void	ft_appeared_before(t_stack *a, int num);
int		ft_num_check(char	*s);
int		ft_input_check(int argc, char **argv, t_stack **a);

//helpers
void	print_stack(t_stack *a, t_stack *b);
int		ft_is_sorted(t_stack *stack);
int		ft_stack_size(t_stack *stack);
int		find_min_index(t_stack *stack);

//sorting helpers
void	ft_sort_array(int *arr, int size);
int		*stack_to_array(t_stack *stack, int size);
void	ft_sort_three(t_stack **a);
void	final_rotation(t_stack **a);
void	push_back_to_a(t_stack **a, t_stack **b);

//sorting
t_cost	calculate_cost(t_stack *a, t_stack *b);
void	do_moves(t_stack **a, t_stack **b, t_cost move);

#endif
