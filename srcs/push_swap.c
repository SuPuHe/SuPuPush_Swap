/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 13:57:20 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_insert_position(t_stack *a, int num)
{
	t_stack	*current;
	t_stack	*tmp;
	int		pos;
	int		min;
	int		max;

	pos = 0;
	current = a;
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

t_cost	calculate_cost(t_stack *a, t_stack *b)
{
	t_stack	*current_b;
	t_cost	best_move;
	int		b_size;
	int		a_size;
	int		idx_b;

	current_b = b;
	b_size = ft_stack_size(b);
	a_size = ft_stack_size(a);
	idx_b = 0;
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

void ft_beggin_sorting(t_stack **a, t_stack **b)
{
	int	*sorted_array;
	int	chunk_size;
	int	chunk_min;
	int	chunk_max;
	int	total;
	int	pushed;
	int	i;
	int	median;

	if (ft_is_sorted(*a))
		return;
	total = ft_stack_size(*a);
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

void	free_split(char **split)
{
	int	i = 0;

	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_input_check_one_arg(char *argv, t_stack **a)
{
	char	**split;
	int		i;
	long	num;
	t_stack	*last;
	t_stack	*new_node;

	last = NULL;
	split = ft_split(argv, ' ');
	if (!split)
		return (ft_printf("Error_split\n"), 1);
	i = 0;
	while (split[i])
	{
		if (!ft_num_check(split[i]))
			return (ft_printf("Error_input\n"), free_split(split), 1);
		num = ft_long_atoi(split[i]);
		if (num > 2147483647 || num < -2147483648)
			return (ft_printf("Error_input\n"), free_split(split), 1);
		ft_appeared_before(*a, num);
		new_node = create_node(num);
		if (!new_node)
			return (ft_printf("Error_not a new node\n"), free_split(split), 1);
		if (!(*a))
			*a = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
	free_split(split);
	return (0);
}

//./push_swap 792517 236241 567811 30810 366999 539143 910778 832234 720003 655380 474070 997208 382154 214190 829348 643905 430156 270029 197359 351947 371271 143473 268608 715651 493912 232139 571785 966861 729703 796877 28720 834011 370663 877194 550184 63741 72723 274193 733545 917691 600405 28023 945957 410561 703404 349812 660100 3603 796175 939339 594959 490335 203874 545153 885040 995091 5653 388292 303316 134584 394658 594311 694238 538200 922386 697678 697235 299804 370725 854701 271054 154142 865561 225155 947099 149227 247248 932833 337814 500627 659762 164418 632377 892638 819182 610098 718253 381574 206783 126821 691028 847931 115220 731102 625407 607510 640003 657586 656466 593077 | wc -l
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	a = NULL;
	if (argc < 2)
		return (ft_printf("Error_less then 2 argc\n"), 1);
	else if (argc == 2)
	{
		if (ft_input_check_one_arg(argv[1], &a) == 1)
			return (1);
	}
	else if (ft_input_check(argc, argv, &a) == 1)
		return (1);
	ft_beggin_sorting(&a, &b);
	print_stack(a, b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
