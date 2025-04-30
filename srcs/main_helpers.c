/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:14:47 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 13:44:23 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_sort_info	init_sort_info(int *sorted_array, int total, int *pushed)
{
	t_sort_info	info;

	info.sorted_array = sorted_array;
	info.total = total;
	info.pushed = pushed;
	info.median = sorted_array[total / 2];
	return (info);
}

void	handle_first_half(t_stack **a, t_stack **b, t_sort_info info)
{
	while (*a && *(info.pushed) < info.total / 2)
	{
		if ((*a)->value < info.median)
		{
			pb(a, b, 0);
			(*(info.pushed))++;
			if (*b && (*b)->value < info.sorted_array[info.total / 4])
				rb(b, 0);
		}
		else
			ra(a, 0);
	}
}

int	get_chunk_size(int total)
{
	if (total <= 100)
		return (total / 5);
	else if (total <= 500)
		return (total / 8);
	else
		return (total / 11);
}
