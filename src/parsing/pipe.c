/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:57:14 by ticasali         ###   ########.fr       */
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
	const char		*null = NULL;
	size_t			i;

	i = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (args->actual_size > 0)
	{
		if (vec_append(args, &null))
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
		return (i);
	}
	token_error(NULL, '|');
	return (-1);
}
