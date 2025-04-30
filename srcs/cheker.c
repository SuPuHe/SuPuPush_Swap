/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:38 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 14:16:56 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_moves(char *str)
{
	if (
		ft_strncmp(str, "sa\n", 3) == 0 ||
		ft_strncmp(str, "sb\n", 3) == 0 ||
		ft_strncmp(str, "ss\n", 3) == 0 ||
		ft_strncmp(str, "pa\n", 3) == 0 ||
		ft_strncmp(str, "pb\n", 3) == 0 ||
		ft_strncmp(str, "ra\n", 3) == 0 ||
		ft_strncmp(str, "rb\n", 3) == 0 ||
		ft_strncmp(str, "rr\n", 3) == 0 ||
		ft_strncmp(str, "rra\n", 4) == 0 ||
		ft_strncmp(str, "rrb\n", 4) == 0 ||
		ft_strncmp(str, "rrr\n", 4) == 0
	)
		return (0);
	return (ft_printf("Error\n"), 1);
}

void	ft_execute_move(char *str, t_stack **a, t_stack **b)
{
	if (ft_strncmp(str, "sa\n", 3) == 0)
		sa(a, 1);
	else if (ft_strncmp(str, "sb\n", 3) == 0)
		sb(b, 1);
	else if (ft_strncmp(str, "ss\n", 3) == 0)
		ss(a, b, 1);
	else if (ft_strncmp(str, "pa\n", 3) == 0)
		pa(a, b, 1);
	else if (ft_strncmp(str, "pb\n", 3) == 0)
		pb(a, b, 1);
	else if (ft_strncmp(str, "ra\n", 3) == 0)
		ra(a, 1);
	else if (ft_strncmp(str, "rb\n", 3) == 0)
		rb(b, 1);
	else if (ft_strncmp(str, "rr\n", 3) == 0)
		rr(a, b, 1);
	else if (ft_strncmp(str, "rra\n", 4) == 0)
		rra(a, 1);
	else if (ft_strncmp(str, "rrb\n", 4) == 0)
		rrb(b, 1);
	else if (ft_strncmp(str, "rrr\n", 4) == 0)
		rrr(a, b, 1);
}

void	ft_get_move(t_stack **a, t_stack **b)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_check_moves(line) == 1)
		{
			free(line);
			exit (1);
		}
		ft_execute_move(line, a, b);
		free(line);
		line = get_next_line(0);
		if (!line)
			break ;
	}
	//free(line);
}

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
	ft_get_move(&a, &b);
	if (ft_is_sorted(a) == 1 && ft_stack_size(b) == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_stack(&a);
	free_stack(&b);
	return (0);
}
