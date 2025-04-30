/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:22:02 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 13:43:20 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **a, int helper)
{
	t_stack	*first;
	t_stack	*second;

	if (!*a || !(*a)->next)
		return ;
	first = *a;
	second = (*a)->next;
	first->next = second->next;
	second->next = first;
	*a = second;
	if (helper == 0)
		ft_printf("sa\n");
}

void	sb(t_stack **b, int helper)
{
	t_stack	*first;
	t_stack	*second;

	if (!*b || !(*b)->next)
		return ;
	first = *b;
	second = (*b)->next;
	first->next = second->next;
	second->next = first;
	*b = second;
	if (helper == 0)
		ft_printf("sb\n");
}

void	ss(t_stack **a, t_stack **b, int helper)
{
	sa(a, 1);
	sb(b, 1);
	if (helper == 0)
		ft_printf("ss\n");
}

void	pa(t_stack **a, t_stack **b, int helper)
{
	t_stack	*temp;

	if (!*b)
		return ;
	temp = *b;
	*b = (*b)->next;
	temp->next = *a;
	*a = temp;
	if (helper == 0)
		ft_printf("pa\n");
}

void	pb(t_stack **a, t_stack **b, int helper)
{
	t_stack	*temp;

	if (!*a)
		return ;
	temp = *a;
	*a = (*a)->next;
	temp->next = *b;
	*b = temp;
	if (helper == 0)
		ft_printf("pb\n");
}
