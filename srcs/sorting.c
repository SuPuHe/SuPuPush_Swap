/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:38 by omizin            #+#    #+#             */
/*   Updated: 2025/05/01 11:57:11 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_moves_alone(t_stack **a, t_stack **b, int cost_a, int cost_b)
{
	while (cost_a > 0)
	{
		ra(a, 0);
		cost_a--;
	}
	while (cost_a < 0)
	{
		rra(a, 0);
		cost_a++;
	}
	while (cost_b > 0)
	{
		rb(b, 0);
		cost_b--;
	}
	while (cost_b < 0)
	{
		rrb(b, 0);
		cost_b++;
	}
}

/**
 * @brief This function performs the moves to sort the stacks based
 * on the calculated costs. It first handles the combined moves
 * (rr and rrr) and then performs the individual moves for each
 * stack. Finally, it pushes the top element from stack b to stack a.
 * @param a The pointer to stack a.
 * @param b The pointer to stack b.
 * @param move The cost structure containing the calculated
 * costs for both stacks.
 */
void	do_moves(t_stack **a, t_stack **b, t_cost move)
{
	int	cost_a;
	int	cost_b;

	cost_a = move.cost_a;
	cost_b = move.cost_b;
	while (cost_a > 0 && cost_b > 0)
	{
		rr(a, b, 0);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(a, b, 0);
		cost_a++;
		cost_b++;
	}
	do_moves_alone(a, b, cost_a, cost_b);
	pa(a, b, 0);
}

static int	return_insert_position(t_stack *a, int num, int min, int max)
{
	t_stack	*tmp;
	int		pos;

	pos = 0;
	if (num < min || num > max)
	{
		tmp = a;
		while (tmp)
		{
			if (tmp->value == max)
				break ;
			pos++;
			tmp = tmp->next;
		}
		return (pos + 1);
	}
	tmp = a;
	while (tmp && tmp->next)
	{
		if (num > tmp->value && num < tmp->next->value)
			return (pos + 1);
		tmp = tmp->next;
		pos++;
	}
	return (0);
}

/**
 * @brief This function finds the position to insert a number in stack a.
 * It checks if the number is less than the minimum or greater
 * than the maximum value in stack a.  If so, it returns the position to
 * insert it at the end of the stack. Otherwise, it finds the correct
 * position to insert it in sorted order.
 * @param a The pointer to stack a.
 * @param num The number to be inserted.
 * @return The position to insert the number in stack a.
 */
int	find_insert_position(t_stack *a, int num)
{
	t_stack	*tmp;
	int		pos;
	int		min;
	int		max;

	tmp = a;
	min = tmp->value;
	max = tmp->value;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	pos = return_insert_position(a, num, min, max);
	return (pos);
}

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
}
