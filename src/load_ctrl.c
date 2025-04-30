/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 01:03:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "commands.h"
#include <stdlib.h>

int	load_ctrl(t_ctrl *ctrl, char **env)
{
	ctrl->environ = env_init(env);
	if (ctrl->environ == NULL)
		return (1);
	ctrl->commands = commands_init(8);
	if (!ctrl->commands.array)
	{
		free_envs(ctrl->environ);
		return (1);
	}
	ctrl->exit = 0;
	ctrl->end = false;
	ctrl->pwd = malloc(sizeof(char) * 4096);
	if (ctrl->pwd == NULL)
	{
		free_envs(ctrl->environ);
		free(ctrl);
		return (1);
		getcwd(ctrl->pwd, 4096);
	}
	ctrl->last_pwd = malloc(sizeof(char) * 4096);
	if (ctrl->last_pwd == NULL)
	{
		free_envs(ctrl->environ);
		free(ctrl->pwd);
		free(ctrl);
		return (1);
	}
	return (0);
}
