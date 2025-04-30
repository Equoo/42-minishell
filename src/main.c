/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:06:04 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 18:06:20 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ctrl	*ctrl;

	(void)(av);
	if (ac != 1)
	{
		write(2, "Bad Arguments\n", 15);
		return (-1);
	}
	ctrl = malloc(sizeof(t_ctrl));
	if (ctrl == NULL)
	{
		write(2, "Bad Allocation\n", 16);
		return (-1);
	}
	load_ctrl(ctrl, env);
	ft_readline(ctrl);
	return (0);
}