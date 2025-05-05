/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 08:32:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_vector.h"
#include "minishell.h"
#include "parsing.h"
#include <asm-generic/errno.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	use_line(t_ctrl *ctrl, char *input)
{
	add_history(input);
	ctrl->commands = commands_init(8);
	if (ctrl->commands.array)
		ctrl->heredocs = vec_new(8, sizeof(t_heredoc));
	if (ctrl->heredocs.data && ctrl->commands.array)
		if (parse_command(ctrl, input) && each_heredocs(ctrl))
			if (execute_pipeline(ctrl) && errno)
				ctrl->end = true;
	if (ctrl->heredocs.data)
		anihilate_heredocs(&ctrl->heredocs);
	if (ctrl->commands.array)
		commands_destroy(&ctrl->commands);
}

void	ft_readline(t_ctrl *ctrl)
{
	char	*input;

	input = NULL;
	while (ctrl->end == false)
	{
		set_signal(true);
		input = readline("-->");
		if (g_sigval)
			ctrl->exit = 130;
		if (errno == EINTR)
			errno = 0;
		if (!input || errno || !set_signal(false))
		{
			if (errno && ft_dprintf(STDERR_FILENO,
					"minishell: %s\n", strerror(errno)))
				ctrl->exit = errno;
			ctrl->end = true;
			break ;
		}
		if (*input)
			use_line(ctrl, input);
		free(input);
		errno = 0;
		g_sigval = 0;
	}
}
