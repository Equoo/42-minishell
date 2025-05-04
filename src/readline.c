/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 19:30:18 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include "parsing.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	use_line(t_ctrl *ctrl, char *input)
{
	add_history(input);
	ctrl->commands = commands_init(8);
	if (ctrl->commands.array)
		if (parse_command(ctrl, input) && each_heredocs(ctrl))
			if (execute_pipeline(ctrl) && errno)
				ctrl->end = true;
	commands_destroy(&ctrl->commands);
}

void	ft_readline(t_ctrl *ctrl)
{
	char	*input;

	while (ctrl->end == false)
	{
		set_signal(true);
		input = readline("-->");
		if (!input || errno || !set_signal(false))
		{
			if (errno)
				ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
			ctrl->exit = 1;
			ctrl->end = true;
			break ;
		}
		if (g_sigval)
			ctrl->exit = 130;
		if (*input)
			use_line(ctrl, input);
		free(input);
		g_sigval = 0;
	}
}
