/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:32:21 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 12:52:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include "commands.h"
#include "environ.h"
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>

int	verbose_pipeline(t_commands cmds)
{
	size_t i;

	i = 0;
	while (i < cmds.len)
	{
		t_command cmd = cmds.array[i];
		ft_printf("Command %u:\n", i);
		size_t j = 0;
		ft_printf("\tArgs:\n");
		while (cmd.args[j])
		{
			ft_printf("\t\tArg %u: \"%s\"\n", j, cmd.args[j]);
			j++;
		}
		ft_printf("\tInput type: %d\n", cmd.in.type);
		if (cmd.in.type == IO_INFILE)
			ft_printf("\t\tInput file: %s\n", cmd.in.file.path);
		else if (cmd.in.type == IO_HEREDOC)
			ft_printf("\t\tInput heredoc: %s\n", cmd.in.file.path);
		else if (cmd.in.type == IO_PIPE)
			ft_printf("\t\tInput pipe from last\n");
		ft_printf("\tOutput type: %d\n", cmd.out.type);
		if (cmd.out.type == IO_OUTFILE)
			ft_printf("\t\tOutput file: %s, append: %d\n", cmd.out.file.path, cmd.out.file.append);
		else if (cmd.out.type == IO_PIPE)
			ft_printf("\t\tOutput pipe to next\n");
		i++;
	}
	return (0);
}

int	execute_pipeline(t_ctrl *ctrl)
{
	t_commands	*cmds;
	size_t			j;

	cmds = &ctrl->commands;
	if (VERBOSE)
		verbose_pipeline(*cmds);
	j = -1;
	while (++j < ctrl->commands.len)
	{
		if (ctrl->commands.array[j].args == NULL || ctrl->commands.array[j].status == -1)
			continue ;
		errno = 0;
		if (ctrl->commands.array[j].in.type & IO_INFILE)
			ctrl->commands.array[j].in.fd = open_file(ctrl->commands.array[j].in.file.path, O_RDONLY);
		if (ctrl->commands.array[j].out.type & IO_PIPE && j + 1 < ctrl->commands.len && ctrl->commands.array[j + 1].in.type == IO_PIPE)
			open_pipe(&ctrl->commands.array[j].out, &ctrl->commands.array[j + 1].in);
		if (command_exec(ctrl, j, env_to_array(ctrl->environ)) + 1)
			return (1);
	}
	commands_close_fds(ctrl->commands);
	j = -1;
	while (++j < ctrl->commands.len)
	{
		if (!ctrl->commands.array[j].args || ctrl->commands.array[j].status == -1)
			continue ;
		if (ctrl->commands.array[j].pid != -1)
			waitpid(ctrl->commands.array[j].pid, &ctrl->commands.array[j].status, 0);
		ft_printf("%s exit with status: %d\n", ctrl->commands.array[j].args[0], ctrl->commands.array[j].status);
	}
	return (0);
}
