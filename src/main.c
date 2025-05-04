/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:06:04 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 10:04:55 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "minishell.h"
#include <stdio.h>

short	g_sigval = 0;

int	main(int ac, char **av, char **env)
{
	t_ctrl	ctrl;

	(void)(av);
	if (ac != 1)
	{
		write(2, "Bad Arguments\n", 15);
		return (-1);
	}
	if (load_ctrl(&ctrl, env) || !set_signal())
	{
		perror("Error: Failed to load environment\n");
		return (-1);
	}
	ft_readline(&ctrl);
	free_envs(ctrl.environ);
	return (ctrl.exit);
}
