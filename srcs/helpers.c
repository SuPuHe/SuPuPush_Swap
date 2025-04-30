/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:51 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 13:43:42 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *a, t_stack *b)
{
	ft_printf("a		b\n");
	while (a != NULL || b != NULL)
	{
		if (a)
		{
			ft_printf("%d", a->value);
			a = a->next;
		}
		else
			ft_printf(" ");
		ft_printf("		");
		if (b)
		{
			ft_printf("%d", b->value);
			b = b->next;
		}
		ft_printf("\n");
	}
}

void	rrr(t_stack **a, t_stack **b, int helper)
{
	rra(a, 1);
	rrb(b, 1);
	if (helper == 0)
		ft_printf("rrr\n");
}

int	ft_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	ft_stack_size(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

int	find_min_index(t_stack *stack)
{
	int		min;
	int		index;
	int		i;
	t_stack	*tmp;

	min = stack->value;
	index = 0;
	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value < min)
		{
			min = tmp->value;
			index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (index);
}
