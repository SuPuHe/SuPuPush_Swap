/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 16:26:28 by omizin           ###   ########.fr       */
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
			pb(a, b);
			(*(info.pushed))++;
			if (*b && (*b)->value < info.sorted_array[info.total / 4])
				rb(b, 0);
		}
		else
			ra(a, 0);
	}
}

int	find_top_distance(t_stack *a, int min, int max)
{
	t_stack	*tmp;
	int		dist;

	tmp = a;
	dist = 0;
	while (tmp)
	{
		if (tmp->value >= min && tmp->value <= max)
			return (dist);
		dist++;
		tmp = tmp->next;
	}
	return (-1);
}

void	move_and_push(t_stack **a, t_stack **b, t_chunk_info cinfo, t_sort_info sinfo)
{
	int	i;

	if (cinfo.top_dist <= cinfo.size / 2)
	{
		i = cinfo.top_dist;
		while (i-- > 0)
			ra(a, 0);
	}
	else
	{
		i = cinfo.size - cinfo.top_dist;
		while (i-- > 0)
			rra(a, 0);
	}
	pb(a, b);
	(*(sinfo.pushed))++;
	if (*(sinfo.pushed) >= sinfo.total - 3)
		return;
	if (*b && (*b)->value < sinfo.median &&
		(*b)->next && (*b)->value < (*b)->next->value)
		rb(b, 0);
}

void	handle_remaining_chunks(t_stack **a, t_stack **b, t_sort_info info, int chunk_size)
{
	int				i;
	int				chunk_min;
	int				chunk_max;
	int				top_dist;
	t_chunk_info	cinfo;

	i = 0;
	while (*a && *(info.pushed) < info.total - 3)
	{
		chunk_min = info.sorted_array[i];
		if (i + chunk_size - 1 >= info.total)
			chunk_max = info.sorted_array[info.total - 1];
		else
			chunk_max = info.sorted_array[i + chunk_size - 1];
		while (*a)
		{
			top_dist = find_top_distance(*a, chunk_min, chunk_max);
			if (top_dist == -1)
				break;
			cinfo.top_dist = top_dist;
			cinfo.size = ft_stack_size(*a);
			move_and_push(a, b, cinfo, info);
			if (*(info.pushed) >= info.total - 3)
				break;
		}
		i += chunk_size;
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

void	ft_beggin_sorting(t_stack **a, t_stack **b)
{
	int			*sorted_array;
	int			chunk_size;
	int			total;
	int			pushed;
	t_sort_info	info;

	if (!*a || ft_is_sorted(*a))
		return;
	total = ft_stack_size(*a);
	sorted_array = stack_to_array(*a, total);
	if (!sorted_array)
		return;
	ft_sort_array(sorted_array, total);
	chunk_size = get_chunk_size(total);
	pushed = 0;
	info = init_sort_info(sorted_array, total, &pushed);
	handle_first_half(a, b, info);
	handle_remaining_chunks(a, b, info, chunk_size);
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
