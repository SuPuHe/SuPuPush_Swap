/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/24 11:51:50 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_long_atoi(const char *string)
{
	int		i;
	int		negative;
	long	result;

	i = 0;
	negative = 1;
	result = 0;
	while (string[i] == ' ' || (string[i] >= 9 && string[i] <= 13))
		i++;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			negative *= -1;
		i++;
	}
	while (string[i] >= '0' && string[i] <= '9')
	{
		result = (result * 10) + (string[i] - 48);
		i++;
	}
	return (result * negative);
}

t_stack	*create_node(long value)
{
	t_stack *new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_appeared_before(t_stack *a, int num)
{
	while(a != NULL)
	{
		if (a->value == num)
		{
			ft_printf("Error_num appeared before\n");
			exit(1);
		}
		a = a->next;
	}
}

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


void	sa(t_stack **a)
{
	t_stack	*first;
	t_stack	*second;

	if (!*a || !(*a)->next)
		return;
	first = *a;
	second = (*a)->next;
	first->next = second->next;
	second->next = first;
	*a = second;
	ft_printf("sa\n");
}

void	sb(t_stack **b)
{
	t_stack	*first;
	t_stack	*second;

	if (!*b || !(*b)->next)
		return;
	first = *b;
	second = (*b)->next;
	first->next = second->next;
	second->next = first;
	*b = second;
	ft_printf("sb\n");
}

void	ss(t_stack **a, t_stack **b)
{
	sa(a);
	sb(b);
	ft_printf("ss\n");
}

void	pa(t_stack **a, t_stack **b)
{
	t_stack	*temp;

	if (!*b)
		return;
	temp = *b;
	*b = (*b)->next;
	temp->next = *a;
	*a = temp;
	ft_printf("pa\n");
}

void	pb(t_stack **a, t_stack **b)
{
	t_stack	*temp;

	if (!*a)
		return;
	temp = *a;
	*a = (*a)->next;
	temp->next = *b;
	*b = temp;
	ft_printf("pb\n");
}

void	ra(t_stack **a)
{
	t_stack	*first;
	t_stack	*last;

	if (!*a || !(*a)->next)
		return;
	first = *a;
	*a = first->next;
	first->next = NULL;
	last = *a;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("ra\n");
}

void	rb(t_stack **b)
{
	t_stack	*first;
	t_stack	*last;

	if (!*b || !(*b)->next)
		return;
	first = *b;
	*b = first->next;
	first->next = NULL;
	last = *b;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("rb\n");
}

void	rr(t_stack **a, t_stack **b)
{
	ra(a);
	rb(b);
	ft_printf("rr\n");
}

void	rra(t_stack **a)
{
	t_stack	*prev;
	t_stack	*last;

	if (!a || !*a || !(*a)->next)
		return;
	prev = NULL;
	last = *a;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *a;
	*a = last;
	ft_printf("rra\n");
}

void	rrb(t_stack **b)
{
	t_stack	*prev;
	t_stack	*last;

	if (!b || !*b || !(*b)->next)
		return;
	prev = NULL;
	last = *b;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *b;
	*b = last;
	ft_printf("rrb\n");
}

void	rrr(t_stack **a, t_stack **b)
{
	rra(a);
	rrb(b);
	ft_printf("rrr\n");
}

int	ft_num_check(char	*s)
{
	if (s[0] >= '0' && s[0] <= '9')
		return (1);
	else if ((s[0] == '+' || s[0] == '-') && (s[1] >= '0' && s[1] <= '9'))
		return (1);
	else
		return (0);
}

int	ft_input_check(int argc, char **argv, t_stack **a)
{
	int		i;
	long	num;
	t_stack	*last;
	t_stack	*new_node;

	last = NULL;
	i = 1;
	while (i < argc)
	{
		num = ft_long_atoi(argv[i]);
		if ((num > 2147483647 || num < -2147483648) || !(ft_num_check(argv[i])))
			return (ft_printf("Error_input\n"), 1);
		ft_appeared_before(*a, num);
		new_node = create_node(num);
		if (!new_node)
			return (ft_printf("Error_not a new node\n"), 1);
		if (!(*a))
			*a = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
	return (0);
}


// void	ft_beggin_sorting(t_stack **a, t_stack **b, int argc)
// {
// 	int	i;
// 	int	half;

// 	half = (argc - 1) / 2;
// 	i = 0;
// 	while (i < half)
// 	{
// 		pb(a, b);
// 		i++;
// 	}
// 	// if ((*a)->value > (*a)->next->value && (*b)->value > (*b)->next->value)
// 	// {
// 	// 	ss(a, b);
// 	// }
// 	// if ((*b)->value > (*b)->next->value)
// 	// 	sb(b);
// 	// for (int j = 0; j < 100; j++)
// 	// {
// 	// 	if ((*a)->value > (*a)->next->value)
// 	// 		sa(a);
// 	// 	ra(a);
// 	// }
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	rra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	rra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	rra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	ra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	rra(a);
// 	if ((*a)->value > (*a)->next->value)
// 		sa(a);
// 	rra(a);
// 	if ((*b)->value > (*b)->next->value)
// 		sb(b);
// 	rrb(b);
// 	if ((*b)->value > (*b)->next->value)
// 		sb(b);
// 	rrb(b);
// 	if ((*b)->value > (*b)->next->value)
// 		sb(b);
// 	rrb(b);
// 	// if ((*a)->value > (*b)->value)
// 	// 	pa(a, b);
// 	// ra(a);
// 	// if ((*b)->value > (*b)->next->value)
// 	// 	sb(b);
// }

int	ft_is_sorted(t_stack *stack)
{
	while(stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	ft_is_sorted_desc(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value < stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	should_rotate_up(t_stack *stack)
{
	t_stack	*max;
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	max = stack;
	while (stack)
	{
		if (stack->value > max->value)
		{
			max = stack;
			pos = i;
		}
		stack = stack->next;
		i++;
	}
	return (pos <= i / 2);
}

int	should_rotate_down(t_stack *stack)
{
	t_stack	*max;
	int		pos;
	int i;

	pos = 0;
	i = 0;
	max = stack;
	while (stack)
	{
		if (stack->value > max->value)
		{
			max = stack;
			pos = i;
		}
		stack = stack->next;
		i++;
	}
	return (pos >= i / 2);
}

void	ft_beggin_sorting(t_stack **a, t_stack **b, int argc)
{
	int	i;
	int	half;

	half = (argc - 1) / 2;
	i = 0;
	while (i < half)
	{
		pb(a, b);
		i++;
	}
	int odd = 0;
	if (i % 2 != 0)
		odd = 1;
	int j = 0;
	int	min;
	int	max;
	min = (*a)->value;
	max = (*a)->value;
	while(!(ft_is_sorted(*a)))
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
		if ((*a)->value > max)
			max = (*a)->value;
		if ((*a)->value < min)
			min = (*a)->value;
		if (j < i / 2 + odd)
			rra(a);
		else
			ra(a);
		j++;
		if (j == i)
			j = 0;
	}
	ft_printf("J=%d", j);
	// while((*b))
	// {
	// 	if ((*b)->value < min)
	// }
}



// a               b
// 795             894
// 243             966
// 572             177
// 383             697
// 517             447
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	if (argc < 2)
		return (ft_printf("Error_less then 2 argc\n"), 1);
	if (ft_input_check(argc, argv, &a) == 1)
		return (1);
	ft_beggin_sorting(&a, &b, argc);
	print_stack(a, b);
	return (0);
}
