/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/28 13:28:31 by omizin           ###   ########.fr       */
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

void	ra(t_stack **a, int helper)
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
	if (helper == 0)
		ft_printf("ra\n");
}

void	rb(t_stack **b, int helper)
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
	if (helper == 0)
		ft_printf("rb\n");
}

void	rr(t_stack **a, t_stack **b)
{
	ra(a, 1);
	rb(b, 1);
	ft_printf("rr\n");
}

void	rra(t_stack **a, int helper)
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
	if (helper == 0)
		ft_printf("rra\n");
}

void	rrb(t_stack **b, int helper)
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
	if (helper == 0)
		ft_printf("rrb\n");
}

void	rrr(t_stack **a, t_stack **b)
{
	rra(a, 1);
	rrb(b, 1);
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

int	ft_stack_size(t_stack *stack)
{
	int	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

int	find_max_index(t_stack *stack)
{
	int		max = stack->value;
	int		index = 0;
	int		i = 0;
	t_stack	*tmp = stack;

	while (tmp)
	{
		if (tmp->value > max)
		{
			max = tmp->value;
			index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (index);
}

int	find_min_index(t_stack *stack)
{
	int		min = stack->value;
	int		index = 0;
	int		i = 0;
	t_stack	*tmp = stack;

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

void	ft_sort_array(int *arr, int size)
{
	int	i, j, tmp;

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
	int		*arr = malloc(sizeof(int) * size);
	int		i = 0;

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
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a, 0);
	}
	else if (first > second && second < third && first > third)
		ra(a, 0);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a, 0);
	}
	else if (first < second && second > third && first > third)
		rra(a, 0);
}

int find_insert_position(t_stack *a, int num)
{
	int pos = 0;
	t_stack *current = a;
	t_stack *tmp = a;
	int min = tmp->value;
	int max = tmp->value;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	if (num < min || num > max)
	{
		pos = 0;
		tmp = a;
		while (tmp)
		{
			if (tmp->value == max)
				break;
			pos++;
			tmp = tmp->next;
		}
		return (pos + 1);
	}
	pos = 0;
	current = a;
	while (current && current->next)
	{
		if (num > current->value && num < current->next->value)
			return (pos + 1);
		current = current->next;
		pos++;
	}
	return (0);
}

t_cost calculate_cost(t_stack *a, t_stack *b)
{
	t_stack *current_b = b;
	int b_size = ft_stack_size(b);
	int a_size = ft_stack_size(a);
	int idx_b = 0;
	t_cost best_move;
	best_move.total = 2147483647;

	while (current_b)
	{
		int cost_b;
		if (idx_b <= b_size / 2)
			cost_b = idx_b;
		else
			cost_b = -(b_size - idx_b);
		int pos_in_a = find_insert_position(a, current_b->value);
		int cost_a;
		if (pos_in_a <= a_size / 2)
			cost_a = pos_in_a;
		else
			cost_a = -(a_size - pos_in_a);
		int total_a;
		if (cost_a < 0)
			total_a = -cost_a;
		else
			total_a = cost_a;
		int total_b;
		if (cost_b < 0)
			total_b = -cost_b;
		else
			total_b = cost_b;
		int total = total_a + total_b;
		if (cost_a > 0 && cost_b > 0)
		{
			if (total > total_a + total_b)
				total = total_a + total_b;
		}
		if (cost_a < 0 && cost_b < 0)
		{
			if (total > total_a + total_b)
				total = total_a + total_b;
		}
		if (total < best_move.total)
		{
			best_move.total = total;
			best_move.cost_a = cost_a;
			best_move.cost_b = cost_b;
			best_move.node = current_b;
		}
		idx_b++;
		current_b = current_b->next;
	}
	return (best_move);
}

void do_moves(t_stack **a, t_stack **b, t_cost move)
{
	int cost_a = move.cost_a;
	int cost_b = move.cost_b;

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
	pa(a, b);
}

void	final_rotation(t_stack **a)
{
	int min_index = find_min_index(*a);
	int size_a = ft_stack_size(*a);

	if (min_index <= size_a / 2)
		while (min_index--)
			ra(a, 0);
	else
		while (min_index++ < size_a)
			rra(a, 0);
}

void	push_back_to_a(t_stack **a, t_stack **b)
{
	while (*b)
	{
		t_cost move = calculate_cost(*a, *b);
		do_moves(a, b, move);
	}
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

void ft_beggin_sorting(t_stack **a, t_stack **b, int argc)
{
	int *sorted_array;
	int chunk_size;
	int chunk_min;
	int chunk_max;
	int total;
	int pushed;
	int i;
	int median;

	total = argc - 1;
	if (!*a || !(sorted_array = stack_to_array(*a, total)))
		return;
	ft_sort_array(sorted_array, total);
	median = sorted_array[total / 2];
	if (total <= 100)
		chunk_size = total / 5;
	else if (total <= 500)
		chunk_size = total / 8;
	else
		chunk_size = total / 11;
	pushed = 0;
	i = 0;
	while (*a && pushed < total / 2)
	{
		if ((*a)->value < median)
		{
			pb(a, b);
			pushed++;
			if (*b && (*b)->value < sorted_array[total / 4])
				rb(b, 0);
		}
		else
			ra(a, 0);
	}
	pushed = total / 2;
	while (*a && pushed < total - 3)
	{
		chunk_min = sorted_array[i];
		if (i + chunk_size - 1 >= total)
			chunk_max = sorted_array[total - 1];
		else
			chunk_max = sorted_array[i + chunk_size - 1];
		while (*a)
		{
			int found = 0;
			int size = ft_stack_size(*a);
			t_stack *tmp = *a;
			int top_dist = 0;
			while (tmp)
			{
				if (tmp->value >= chunk_min && tmp->value <= chunk_max)
				{
					found = 1;
					break;
				}
				top_dist++;
				tmp = tmp->next;
			}
			if (!found)
				break;
			if (top_dist <= size / 2)
			{
				while (top_dist-- > 0 && *a)
					ra(a, 0);
			}
			else
			{
				top_dist = size - top_dist;
				while (top_dist-- > 0 && *a)
					rra(a, 0);
			}
			if (*a)
			{
				pb(a, b);
				pushed++;
				if (pushed >= total - 3)
					break;
				if (*b && (*b)->value < median &&
					(*b)->next && (*b)->value < (*b)->next->value)
					rb(b, 0);
			}
		}
		i += chunk_size;
	}
	free(sorted_array);
	if (*a && ft_stack_size(*a) == 3)
		ft_sort_three(a);
	if (*b)
		push_back_to_a(a, b);
	if (*a)
		final_rotation(a);
}


//672 4979
//640 4527


//./push_swap 792517 236241 567811 30810 366999 539143 910778 832234 720003 655380 474070 997208 382154 214190 829348 643905 430156 270029 197359 351947 371271 143473 268608 715651 493912 232139 571785 966861 729703 796877 28720 834011 370663 877194 550184 63741 72723 274193 733545 917691 600405 28023 945957 410561 703404 349812 660100 3603 796175 939339 594959 490335 203874 545153 885040 995091 5653 388292 303316 134584 394658 594311 694238 538200 922386 697678 697235 299804 370725 854701 271054 154142 865561 225155 947099 149227 247248 932833 337814 500627 659762 164418 632377 892638 819182 610098 718253 381574 206783 126821 691028 847931 115220 731102 625407 607510 640003 657586 656466 593077 | wc -l
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	a = NULL;
	if (argc < 2)
		return (ft_printf("Error_less then 2 argc\n"), 1);
	if (ft_input_check(argc, argv, &a) == 1)
		return (1);
	ft_beggin_sorting(&a, &b, argc);
	print_stack(a, b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
