/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 18:07:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_vector.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

int	parse_pipe(t_ctrl *ctrl, char *str, t_command *cmd, t_vector *args)
{
	if (ft_strcmp("|", str))
		return (-2);
	if (args->actual_size > 0)
	{
		if (vec_append_ulong(args, (uintptr_t) NULL))
			return (-1);
		cmd->args = (char **)args->data;
		if (!cmd->out.type)
			cmd->out.type = IO_PIPE;
		if (commands_append(&ctrl->commands, *cmd))
			return (-1);
		*args = vec_new(8, sizeof(char *));
		if (!args->data)
			return (-1);
		*cmd = (t_command){.in.type = IO_PIPE,
			.in.fd = -1, .out.fd = -1, .args = NULL};
		return (0);
	}
	return (-2);
}
