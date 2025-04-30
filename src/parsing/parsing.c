/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:28:00 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 00:30:40 by dderny           ###   ########.fr       */
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

int	parse_command(t_ctrl *ctrl, char *strcmd)
{
	const char		*null = NULL;
	t_command		cmd = {.in.fd = -1, .out.fd = -1, .args = NULL};
	t_vector		args = vec_new(8, sizeof(char *));
	size_t			i;

	i = 0;
	while (!errno && strcmd[i])
	{
		ft_printf("i: %u, char: %c\n", i, strcmd[i]);
		if (strcmd[i] == '<' || strcmd[i] == '>')
			i += parse_redirection(ctrl, strcmd + i, &cmd);
		else if (strcmd[i] == '|')
			i += parse_pipe(ctrl, strcmd + i, &cmd, &args);
		else if (ft_isspace(strcmd[i]) && ++i)
			continue ;
		else
			i += parse_arg(ctrl, strcmd + i, &args);
	}
	if (args.actual_size > 0)
	{
		if (vec_append(&args, &null))
			return (1);
		cmd.args = (char **)args.data;
		if (commands_append(&ctrl->commands, cmd))
			return (1);
	}
	return (0);
}
