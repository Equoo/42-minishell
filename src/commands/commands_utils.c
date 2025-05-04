/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:21:21 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 10:39:16 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	commands_close_fds(t_commands cmds)
{
	t_command	*array;
	size_t		i;

	array = cmds.array;
	i = 0;
	while (i < cmds.len)
	{
		if (array[i].in.fd && array[i].in.fd != -1)
			close(array[i].in.fd);
		if (array[i].out.fd && array[i].out.fd != -1)
			close(array[i].out.fd);
		array[i].in.fd = -1;
		array[i].out.fd = -1;
		i++;
	}
}

int	open_file(char *path, int flags)
{
	int	fd;

	if (flags & O_WRONLY)
		fd = open(path, flags, 0644);
	else
		fd = open(path, flags);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	return (fd);
}

int	open_pipe(t_inout *in_pipe, t_inout *out_pipe)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	in_pipe->fd = pipefd[1];
	out_pipe->fd = pipefd[0];
	return (0);
}

void	redir_fds(t_command *cmd)
{
	if (cmd->in.type && cmd->in.fd <= 0)
		cmd->in.fd = open_file("/dev/null", O_RDONLY);
	if (!errno && cmd->in.type)
		dup2(cmd->in.fd, STDIN_FILENO);
	if (!errno && cmd->out.type && cmd->out.fd <= 0)
		cmd->out.fd = open_file("/dev/null", O_WRONLY);
	if (!errno && cmd->out.type)
		dup2(cmd->out.fd, STDOUT_FILENO);
}

int	print_error_exec(char *str, bool check)
{
	if (check == true)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: is a directory\n",
			str);
		return (126);
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", str,
		strerror(errno));
	return (127);
}
