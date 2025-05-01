/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:28:00 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 16:53:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "commands.h"
#include "ft_printf.h"
#include "ft_vector.h"
#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

static int	parse_per_types(t_ctrl *ctrl, char *strcmd, t_command *cmd, t_vector *args)
{
	size_t			i;

	i = 0;
	while (!errno && strcmd[i])
	{
		if (VERBOSE)
			ft_printf("i: %u, char: %c\n", i, strcmd[i]);
		if (strcmd[i] == '<' || strcmd[i] == '>')
			i += parse_redirection(ctrl, strcmd + i, cmd);
		else if (strcmd[i] == '|')
			i += parse_pipe(ctrl, strcmd + i, cmd, args);
		else if (ft_isspace(strcmd[i]) && ++i)
			continue ;
		else
			i += parse_arg(ctrl, strcmd + i, args);
	}
	if (errno && cmd->args)
		ft_freearray((void **)cmd->args);
	return (0);
}

int	parse_command(t_ctrl *ctrl, char *strcmd)
{
	const char		*null = NULL;
	t_command		cmd;
	t_vector		args;

	cmd = (t_command){.in.fd = -1, .out.fd = -1, .args = NULL};
	args = vec_new(8, sizeof(char *));
	if (!args.data || parse_per_types(ctrl, strcmd, &cmd, &args))
		return (0);
	if (args.actual_size > 0)
	{
		cmd.args = (char **)args.data;
		if (vec_append(&args, &null) || commands_append(&ctrl->commands, cmd))
		{
			ft_freearray((void **)cmd.args);
			return (0);
		}
	}
	else if (cmd.in.type == IO_PIPE || cmd.out.type == IO_PIPE)
	{
		token_error(NULL, '|');
		ft_freearray((void **)cmd.args);
		return (0);
	}
	return (1);
}
