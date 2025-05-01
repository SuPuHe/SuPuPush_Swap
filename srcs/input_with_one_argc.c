/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_with_one_argc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:55:41 by omizin            #+#    #+#             */
/*   Updated: 2025/05/01 11:53:52 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief This function creates a new node with the given number and
 * adds it to the end of the stack. It also checks if the number has
 * already appeared in the stack.
 * @param a The pointer to the stack where the new node will be added.
 * @param num The number to be added to the stack.
 * @param split The array of strings containing the input numbers.
 * @return 0 if successful, 1 if there is an error.
*/
static int	ft_input_node_create(t_stack **a, int num, char **split)
{
	t_stack	*last;
	t_stack	*new_node;

	last = NULL;
	if (ft_appeared_before(*a, num) == 1)
		return (1);
	new_node = create_node(num);
	if (!new_node)
	{
		ft_printf("Error_not a new node\n");
		free_split(split);
		return (1);
	}
	if (!(*a))
		*a = new_node;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (0);
}

/**
 * @brief This function checks if the input is valid when there is
 * only one argument. It splits the argument into numbers, checks
 * if they are valid integers, and creates nodes in the stack.
 * @param argv The input string containing numbers separated by spaces.
 * @param a The pointer to the stack where the numbers will be stored.
 * @return 0 if successful, 1 if there is an error.
 */
int	ft_input_check_one_arg(char *argv, t_stack **a)
{
	char	**split;
	int		i;
	long	num;

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
		if (ft_input_node_create(a, num, split) == 1)
			return (free_split(split), 1);
		i++;
	}
	free_split(split);
	return (0);
}
