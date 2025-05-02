/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:32:21 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 18:46:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include "commands.h"
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>

static int	verbose_pipeline(t_commands cmds)
{
	size_t i;

	i = 0;
	while (i < cmds.len)
	{
		t_command cmd = cmds.array[i];
		ft_printf("Command %u:\n", i);
		size_t j = -1;
		ft_printf("\tArgs:\n");
		while (cmd.args[++j])
			ft_printf("\t\tArg %u: \"%s\"\n", j, cmd.args[j]);
		ft_printf("\tInput type: %d\n", cmd.in.type);
		if (cmd.in.type == IO_INFILE)
			ft_printf("\t\tInput file: %s\n", cmd.in.file.path);
		else if (cmd.in.type == IO_HEREDOC)
			ft_printf("\t\tInput heredoc: %s by %s\n", cmd.in.heredoc.end, cmd.in.heredoc.tmpfile);
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

static int	execute_each(t_ctrl *ctrl, t_commands *cmds)
{
	size_t			j;

	j = -1;
	while (++j < cmds->len)
	{
		if (cmds->array[j].args == NULL || cmds->array[j].status == -1)
			continue ;
		errno = 0;
		if (cmds->array[j].in.type & IO_INFILE)
			cmds->array[j].in.fd = open_file(cmds->array[j].in.file.path, O_RDONLY);
		if (cmds->array[j].in.type & IO_HEREDOC)
			cmds->array[j].in.fd = open_file(cmds->array[j].in.heredoc.tmpfile, O_RDONLY);
		if (cmds->array[j].out.type & IO_PIPE && j + 1 < cmds->len && cmds->array[j + 1].in.type == IO_PIPE)
			open_pipe(&cmds->array[j].out, &cmds->array[j + 1].in);
		if (command_exec(ctrl, j) + 1)
			return (1);
	}
	return (0);
}

static void wait_for_children(t_commands *cmds)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < cmds->len)
	{
		if (cmds->array[i].pid > 0)
		{
			waitpid(cmds->array[i].pid, &status, 0);
			if (WIFEXITED(status))
				cmds->array[i].status = WEXITSTATUS(status);
			else
				cmds->array[i].status = 1;
			if (VERBOSE)
				ft_printf("%s exit with status: %d\n", cmds->array[i].args[0], cmds->array[i].status);
		}
		i++;
	}
}

int	execute_pipeline(t_ctrl *ctrl)
{
	t_commands	*cmds;

	cmds = &ctrl->commands;
	if (VERBOSE)
		verbose_pipeline(*cmds);

	if (execute_each(ctrl, cmds))
		return (1);
	commands_close_fds(*cmds);
	wait_for_children(cmds);
	return (0);
}
