/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:52:37 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 13:45:06 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	*stack_to_array(t_stack *stack, int size)
{
	int		*arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	while (i < size && stack)
	{
		arr[i] = stack->value;
		stack = stack->next;
		i++;
	}
	return (arr);
}

void	ft_sort_three(t_stack **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && second < third && first < third)
		sa(a, 0);
	else if (first > second && second > third)
	{
		sa(a, 0);
		rra(a, 0);
	}
	else if (first > second && second < third && first > third)
		ra(a, 0);
	else if (first < second && second > third && first < third)
	{
		sa(a, 0);
		ra(a, 0);
	}
	else if (first < second && second > third && first > third)
		rra(a, 0);
}

void	final_rotation(t_stack **a)
{
	int	min_index;
	int	size_a;

	min_index = find_min_index(*a);
	size_a = ft_stack_size(*a);
	if (min_index <= size_a / 2)
		while (min_index--)
			ra(a, 0);
	else
		while (min_index++ < size_a)
			rra(a, 0);
}

void	push_back_to_a(t_stack **a, t_stack **b)
{
	t_cost	move;

	while (*b)
	{
		move = calculate_cost(*a, *b);
		do_moves(a, b, move);
	}
}
