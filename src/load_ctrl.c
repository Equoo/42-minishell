/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 14:13:23 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "minishell.h"
#include "environ.h"
#include <stdlib.h>
#include <libft.h>
#include "errno.h"

int	load_ctrl(t_ctrl *ctrl, char **env)
{
	ctrl->environ = env_init(env);
	if (errno)
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
