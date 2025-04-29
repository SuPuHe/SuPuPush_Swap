/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_with_one_argc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:55:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 14:57:39 by omizin           ###   ########.fr       */
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

static void	ft_input_node_create(t_stack **a, int num, char **split)
{
	t_stack	*last;
	t_stack	*new_node;

	last = NULL;
	ft_appeared_before(*a, num);
	new_node = create_node(num);
	if (!new_node)
	{
		ft_printf("Error_not a new node\n");
		free_split(split);
		exit(1);
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
}

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
		ft_input_node_create(a, num, split);
		i++;
	}
	free_split(split);
	return (0);
}
