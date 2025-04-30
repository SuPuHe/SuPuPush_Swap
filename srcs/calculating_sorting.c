/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculating_sorting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:50:34 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 10:11:29 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	combined_cost(int cost_a, int cost_b)
{
	int	total_a;
	int	total_b;

	if (cost_a < 0)
		total_a = -cost_a;
	else
		total_a = cost_a;
	if (cost_b < 0)
		total_b = -cost_b;
	else
		total_b = cost_b;
	return (total_a + total_b);
}

static t_cost	calculate_cost_for_node(t_stack *a, t_stack *b,
t_stack *node_b, int idx_b)
{
	t_cost	cost;
	int		b_size;
	int		a_size;
	int		pos_in_a;

	a_size = ft_stack_size(a);
	b_size = ft_stack_size(b);
	if (idx_b <= b_size / 2)
		cost.cost_b = idx_b;
	else
		cost.cost_b = -(b_size - idx_b);
	pos_in_a = find_insert_position(a, node_b->value);
	if (pos_in_a <= a_size / 2)
		cost.cost_a = pos_in_a;
	else
		cost.cost_a = -(a_size - pos_in_a);
	cost.total = combined_cost(cost.cost_a, cost.cost_b);
	cost.node = node_b;
	return (cost);
}

t_cost	calculate_cost(t_stack *a, t_stack *b)
{
	t_stack	*current_b;
	t_cost	best_move;
	t_cost	current;
	int		idx_b;

	current_b = b;
	idx_b = 0;
	best_move.total = 2147483647;
	while (current_b)
	{
		current = calculate_cost_for_node(a, b, current_b, idx_b);
		if (current.total < best_move.total)
			best_move = current;
		idx_b++;
		current_b = current_b->next;
	}
	return (best_move);
}
