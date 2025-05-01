/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 11:28:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "minishell.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	ft_readline(t_ctrl *ctrl)
{
	char	*input;

	while (ctrl->end == false)
	{
		input = readline("-->");
		if (!input)
		{
			ctrl->end = true;
			break ;
		}
		add_history(input);
		ctrl->commands = commands_init(8);
		if (ctrl->commands.array)
			if (parse_command(ctrl, input))
				execute_pipeline(ctrl);
		commands_destroy(&ctrl->commands);
		free(input);
	}
}
