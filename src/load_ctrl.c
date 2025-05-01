/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 11:11:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include <stdlib.h>

int	load_ctrl(t_ctrl *ctrl, char **env)
{
	ctrl->environ = env_init(env);
	if (ctrl->environ == NULL)
		return (1);
	ctrl->exit = 0;
	ctrl->end = false;
	return (0);
}
