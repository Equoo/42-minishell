/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:22:53 by dderny            #+#    #+#             */
/*   Updated: 2025/04/28 07:27:34 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec_fds(t_command *cmd)
{
	if (cmd->in.type && (!cmd->in.fd || cmd->in.fd == -1))
		cmd->in.fd = open_file("/dev/null", O_RDONLY);
	if (!errno && cmd->in.type)
		dup2(cmd->in.fd, STDIN_FILENO);
	if (!errno && cmd->out.type && (!cmd->out.fd || cmd->out.fd == -1))
		open_file("/dev/null", O_WRONLY | O_CREAT | O_TRUNC);
	if (!errno && cmd->out.type)
		dup2(cmd->out.fd, STDOUT_FILENO);
}

int	command_exec(t_commands cmds, int i, char **environ)
{
	t_command	*cmd;
	pid_t		child;

	cmd = cmds.array + i;
	child = fork();
	if (child)
	{
		cmd->pid = child;
		return (-1);
	}
	if (VERBOSE)
		ft_printf("%s: in %d out %d\n", cmd->binary, cmd->in.type ? cmd->in.fd :
			-1, cmd->out.type ? cmd->out.fd : -1);
	exec_fds(cmd);
	commands_close_fds(cmds);
	if (cmd->binary && cmd->args && !errno && !access(cmd->binary, R_OK | X_OK))
		execve(cmd->binary, cmd->args, environ);
	// if (cmd->out.type == F_PIPE)
	// close(cmds.array[cmd->out.pipeout].in.fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!errno)
		return (0);
	perror(cmd->binary);
	return (127);
}
