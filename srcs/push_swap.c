/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:52:41 by omizin            #+#    #+#             */
/*   Updated: 2025/04/30 16:18:35 by omizin           ###   ########.fr       */
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
		return (ft_printf("Error_less then 2 argc\n"), 1);
	else if (argc == 2)
	{
		if (ft_input_check_one_arg(argv[1], &a) == 1)
			return (1);
	}
	else if (ft_input_check(argc, argv, &a) == 1)
		return (1);
	ft_beggin_sorting(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
