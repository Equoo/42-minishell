/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 06:42:13 by ticasali         ###   ########.fr       */
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
		parse_command(ctrl, input);
		execute_pipeline(ctrl);
		commands_destroy(&ctrl->commands);
		free(input);
		ctrl->commands = commands_init(8);
	}
}
