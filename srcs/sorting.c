/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:38 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 16:26:51 by omizin           ###   ########.fr       */
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

void	do_moves(t_stack **a, t_stack **b, t_cost move)
{
	int	cost_a;
	int	cost_b;

	cost_a = move.cost_a;
	cost_b = move.cost_b;
	while (cost_a > 0 && cost_b > 0)
	{
		rr(a, b);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(a, b);
		cost_a++;
		cost_b++;
	}
	do_moves_alone(a, b, cost_a, cost_b);
	pa(a, b);
}
