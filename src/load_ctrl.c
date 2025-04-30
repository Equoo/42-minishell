/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 17:57:39 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ctrl	*load_ctrl(t_ctrl *ctrl, char **env)
{
	ctrl->environ = lst_init(env);
	if (ctrl->environ == NULL)
	{
		free(ctrl);
		return (NULL);
	}
	ctrl->exit = 0;
	ctrl->end = false;
	ctrl->pwd = malloc(sizeof(char) * 4096);
	if (ctrl->pwd == NULL)
	{
		free_lst(ctrl->environ);
		free(ctrl);
		return (NULL);
		getcwd(ctrl->pwd, 4096);
	}
	ctrl->last_pwd = malloc(sizeof(char) * 4096);
	if (ctrl->last_pwd == NULL)
	{
		free_lst(ctrl->environ);
		free(ctrl->pwd);
		free(ctrl);
		return (NULL);
	}
	return (ctrl);
}
