/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:10:34 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 13:44:35 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief This function finds the top distance of the first element in stack a
 * that is within the specified range (min to max).
 * It returns the distance from the top of the stack to that element.
 * @param a The pointer to stack a.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return The distance from the top of the stack to the first element within the range.
 */
static int	find_top_distance(t_stack *a, int min, int max)
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

/**
 * @brief This function moves the top element of stack a to stack b if it is within the chunk range.
 * It also rotates stack a if the top element is not within the chunk range.
 * @param a The pointer to stack a.
 * @param b The pointer to stack b.
 * @param cinfo The chunk information structure containing top distance and size.
 * @param sinfo The sorting information structure containing median and total elements.
 */
static void	move_and_push(t_stack **a, t_stack **b,
t_chunk_info cinfo, t_sort_info sinfo)
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
	pb(a, b, 0);
	(*(sinfo.pushed))++;
	if (*(sinfo.pushed) >= sinfo.total - 3)
		return ;
	if (*b && (*b)->value < sinfo.median
		&& (*b)->next && (*b)->value < (*b)->next->value)
		rb(b, 0);
}

static int	find_chunk_max(int i, int chunk_size, t_sort_info info)
{
	int	chunk_max;

	if (i + chunk_size - 1 >= info.total)
		chunk_max = info.sorted_array[info.total - 1];
	else
		chunk_max = info.sorted_array[i + chunk_size - 1];
	return (chunk_max);
}

/**
 * @brief This function handles the remaining chunks of elements in stack a.
 * It pushes elements from stack a to stack b based on their value compared to the chunk range.
 * It continues until all elements are sorted or pushed back to stack a.
 * @param a The pointer to stack a.
 * @param b The pointer to stack b.
 * @param info The sorting information structure containing sorted array and total elements.
 * @param chunk_size The size of each chunk for sorting.
 */
static void	handle_remaining_chunks(t_stack **a, t_stack **b,
t_sort_info info, int chunk_size)
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
		chunk_max = find_chunk_max(i, chunk_size, info);
		while (*a)
		{
			top_dist = find_top_distance(*a, chunk_min, chunk_max);
			if (top_dist == -1)
				break ;
			cinfo.top_dist = top_dist;
			cinfo.size = ft_stack_size(*a);
			move_and_push(a, b, cinfo, info);
			if (*(info.pushed) >= info.total - 3)
				break ;
		}
		i += chunk_size;
	}
}

/**
 * @brief This function begins the sorting process for the given stacks.
 * It checks if stack a is empty or already sorted, and if not, it sorts the elements
 * by pushing them to stack b and then back to stack a.
 * @param a The pointer to stack a.
 * @param b The pointer to stack b.
 */
void	ft_beggin_sorting(t_stack **a, t_stack **b)
{
	int			*sorted_array;
	int			chunk_size;
	int			total;
	int			pushed;
	t_sort_info	info;

	if (!*a || ft_is_sorted(*a))
		return ;
	total = ft_stack_size(*a);
	sorted_array = stack_to_array(*a, total);
	if (!sorted_array)
		return ;
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
