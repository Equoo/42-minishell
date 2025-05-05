/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:06:04 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 07:46:59 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environ.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

volatile short	g_sigval = 0;

int	main(int ac, char **av, char **env)
{
	t_ctrl	ctrl;

	(void)(av);
	if (ac != 1)
	{
		write(2, "Bad Arguments\n", 15);
		return (-1);
	}
	ctrl = (t_ctrl){0};
	if (load_ctrl(&ctrl, env))
	{
		perror("Error: Failed to load environment\n");
		return (-1);
	}
	ft_export_exec(&ctrl, ft_strdup("PWD"),
		getcwd(NULL, 0));
	ft_readline(&ctrl);
	free_envs(ctrl.environ);
	write(STDOUT_FILENO, "exit\n", 5);
	return (ctrl.exit);
}
