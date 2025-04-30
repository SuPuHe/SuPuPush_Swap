/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:39:54 by omizin            #+#    #+#             */
/*   Updated: 2025/04/29 13:42:56 by omizin           ###   ########.fr       */
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
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_appeared_before(t_stack *a, int num)
{
	while (a != NULL)
	{
		if (a->value == num)
		{
			ft_printf("Error_num appeared before\n");
			return (1);
		}
		a = a->next;
	}
	return (0);
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
/**
 * @brief Checks if the input is valid and creates a linked list of nodes.
 * @param argc The number of arguments.
 * @param argv The array of arguments.
 * @param a Pointer to the head of the linked list.
 * @return 0 on success, 1 on error.
*/
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
		if (ft_appeared_before(*a, num) == 1)
			return (1);
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
