/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:20:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 22:50:55 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "parsing.h"
#include "commands.h"
#include "ft_vector.h"
#include "libft.h"
#include "minishell.h"
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

size_t	skip_backslash(char quotes[2], size_t i, char *str)
{
	if (!quotes[0] && str[i] == '\\'
		&& str[i + 1] && ft_strchr("<>|\\", str[i + 1]))
		return (++i);
	return (i);
}

static void	last_command_free(t_command cmd)
{
	if (cmd.in.fd >= 0)
		close(cmd.in.fd);
	if (cmd.out.fd >= 0)
		close(cmd.out.fd);
	if (cmd.in.type == IO_INFILE)
		free(cmd.in.file.path);
	if (cmd.out.type == IO_OUTFILE)
		free(cmd.out.file.path);
	if (cmd.in.type == IO_HEREDOC)
		free(cmd.in.heredoc.end);
}

int	last_command(t_command cmd, t_ctrl *ctrl, t_vector args)
{
	if (cmd.status >= -1 && args.actual_size > 0)
	{
		cmd.args = (char **)args.data;
		if (vec_append_ulong(&args, (uintptr_t) NULL)
			|| commands_append(&ctrl->commands, cmd))
		{
			ft_freearray((void **)cmd.args);
			return (0);
		}
		return (1);
	}
	if (cmd.status == -2 || (cmd.in.type == IO_PIPE || (ctrl->commands.len > 0
				&& ctrl->commands.array[ctrl->commands.len - 1]
				.out.type == IO_PIPE)))
		token_error(NULL, '|');
	if (cmd.status == -3)
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token 'newline'\n");
	last_command_free(cmd);
	if (args.data)
		ft_freearray((void **)args.data);
	return (0);
}

int	vec_secure(t_vector *vec, char *val)
{
	u_long	lo;

	if (errno)
		return (0);
	lo = (uintptr_t)(val);
	vec_append(vec, &lo);
	return (0);
}

t_vector	secure_expand_operators(char *str)
{
	t_vector	expand;
	size_t		i;

	expand = vec_from_string(str);
	i = 0;
	while (!errno && i < (size_t)expand.actual_size)
	{
		if (ft_strchr("<>|\\", ((char *)expand.data)[i]))
			vec_insert_int(&expand, '\\', i++);
		i++;
	}
	return (expand);
}
