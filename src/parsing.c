/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:05:23 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 07:19:04 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	parsing(char *str)
{
	t_commands	cmds;
	char	**tab;
	size_t	ct;

	ct = 0;
	if (check_parsing(str) == false)
		return ;	//perror(BAD SYNTAX)
	cmds = commands_init(count_pipe(str) + 1);
	if (!cmds.array)
		return ;	//perror(BAD MALLOC)
	tab = ft_quote_split(str, '|');
	if (tab == NULL)
		return ;	//perror(BAD MALLOC)
	while (ct < cmds.len)
	{
		if (check_cmd(tab[ct]) == false)
		{
			commands_destroy(&cmds);
			return ;	//perror(BAD SYNTAX)
		}
		if (commands_append(&cmds, create_cmd(tab[ct])))
		{
			free(cmds.array->binary);
			free(cmds.array->args);
			commands_destroy(&cmds);	//perror(BAD MALLOC)
			return ;
		}
	}
}

t_command	create_cmd(char *str)
{
	t_command	cmd = {.in.fd = -1, .out.fd = -1, .binary = NULL, .args = NULL};

	
}