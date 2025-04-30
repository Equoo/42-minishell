/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 18:06:23 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	ft_readline(t_ctrl *ctrl)
{
	char	*input;

	while (ctrl->end == false)
	{
		input = readline("-->");
		add_history(input);
		ctrl->commands = parsing(input);
		//Exec Pipex
	}
	//free_all_struct
}