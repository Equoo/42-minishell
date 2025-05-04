/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:33:05 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 00:57:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_vector.h"
#include "minishell.h"
#include "environ.h"
#include <libft.h>
#include <stdlib.h>
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

void	anihilate_heredocs(t_vector *vec)
{
	t_heredoc	*hd;
	ssize_t		i;

	i = 0;
	while (i < vec->actual_size)
	{
		hd = &((t_heredoc *)vec->data)[i];
		if (hd->end)
			free(hd->end);
		i++;
	}
	vec_destroy(vec);
}

void	free_ctrl(t_ctrl *ctrl)
{
	if (ctrl->environ)
		free_envs(ctrl->environ);
	if (ctrl->heredocs.data)
		anihilate_heredocs(&ctrl->heredocs);
	if (ctrl->commands.array)
		commands_destroy(&ctrl->commands);
}
