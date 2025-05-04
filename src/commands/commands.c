/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:53:23 by dderny            #+#    #+#             */
/*   Updated: 2025/05/05 00:52:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_vector.h"
#include "minishell.h"

t_commands	commands_init(size_t size)
{
	t_commands	commands;

	commands.array = ft_calloc(size, sizeof(t_command));
	if (!commands.array)
		return ((t_commands){0});
	commands.size = size;
	commands.len = 0;
	return (commands);
}

int	commands_append(t_commands *cmds, t_command cmd)
{
	t_command	*data;

	if (cmds->len >= cmds->size)
	{
		cmds->size <<= 1;
		data = malloc(cmds->size * sizeof(t_command));
		if (!data)
		{
			free(cmds->array);
			return (1);
		}
		ft_memcpy(data, cmds->array, cmds->len * sizeof(t_command));
		ft_bzero(data + cmds->len * sizeof(t_command),
			(cmds->size - cmds->len) * sizeof(t_command));
		free(cmds->array);
		cmds->array = data;
	}
	cmds->array[cmds->len] = cmd;
	cmds->len++;
	return (0);
}

void	commands_destroy(t_commands *cmds)
{
	size_t	i;
	size_t	j;

	if (!cmds->array)
		return ;
	i = -1;
	while (++i < cmds->len)
	{
		if (cmds->array[i].binary)
			free(cmds->array[i].binary);
		if (cmds->array[i].args)
		{
			j = 0;
			while (cmds->array[i].args[j])
				free(cmds->array[i].args[j++]);
			free(cmds->array[i].args);
		}
		if (cmds->array[i].in.type & IO_INFILE)
			free(cmds->array[i].in.file.path);
		if (cmds->array[i].out.type & IO_OUTFILE)
			free(cmds->array[i].out.file.path);
	}
	free_commands(cmds);
}

void	free_commands(t_commands *cmds)
{
	free(cmds->array);
	cmds->array = NULL;
	cmds->size = 0;
	cmds->len = 0;
}

int	exit_commands(t_ctrl *ctrl, int status)
{
	if (ctrl->close_in)
		close(STDIN_FILENO);
	if (ctrl->close_out)
		close(STDOUT_FILENO);
	free_ctrl(ctrl);
	exit(status);
	return (0);
}
