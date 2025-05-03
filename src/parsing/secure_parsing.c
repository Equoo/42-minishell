/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:20:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 19:07:08 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	skip_backslash(char quotes[2], size_t i, char *str)
{
	if (!quotes[0] && str[i] == '\\'
		&& str[i + 1] && ft_strchr("<>|\\", str[i + 1]))
		return (++i);
	return (i);
}

int	last_command(t_command cmd, t_ctrl *ctrl, t_vector args)
{
	if (args.actual_size > 0)
	{
		cmd.args = (char **)args.data;
		if (vec_append_ulong(&args, (uintptr_t) NULL)
			|| commands_append(&ctrl->commands, cmd))
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

int	vec_secure(t_vector *vec, char *val)
{
	u_long	lo;

	if (errno)
		return (0);
	lo = (uintptr_t)(val);
	vec_append(vec, &lo);
	return (0);
}
