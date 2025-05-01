/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/05/01 11:28:28 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	a = NULL;
	if (argc < 2)
		return (0);
	else if (argc == 2)
	{
		if (ft_input_check_one_arg(argv[1], &a) == 1)
			return (free_stack(&a), free_stack(&b), 1);
	}
	else if (ft_input_check(argc, argv, &a) == 1)
		return (free_stack(&a), free_stack(&b), 1);
	ft_beggin_sorting(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
