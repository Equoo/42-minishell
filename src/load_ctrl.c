/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 16:53:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "minishell.h"
#include "environ.h"
#include <stdlib.h>
#include <libft.h>

int	load_ctrl(t_ctrl *ctrl, char **env)
{
	ctrl->environ = env_init(env);
	if (ctrl->environ == NULL)
		return (1);
	ctrl->exit = 0;
	ctrl->end = false;
	return (0);
}

void	free_ctrl(t_ctrl *ctrl)
{
	if (ctrl->environ)
		free_envs(ctrl->environ);
	if (ctrl->commands.array)
		commands_destroy(&ctrl->commands);
}
