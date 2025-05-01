/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:21:21 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 14:39:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void commands_close_fds(t_commands cmds)
{
	t_command	*array;
	size_t			i;

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

int open_file(char *path, int flags)
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

int open_pipe(t_inout *in_pipe, t_inout *out_pipe)
{
	int pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	in_pipe->fd = pipefd[1];
	out_pipe->fd = pipefd[0];
	return (0);
}
