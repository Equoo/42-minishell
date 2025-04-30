/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/30 20:59:36 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "commands.h"
#include "parsing.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	parse_redirection(t_ctrl *ctrl, char *str, t_command *cmd)
{
	t_token_type	type;
	char			*token;
	size_t			i;
	
	i = 0;
	type = TOKEN_APPEND;
	if (str[i] == '<' && ++i)
		type = TOKEN_RIN;
	else if (str[i] == '>' && ++i)
		type = TOKEN_ROUT;
	if (type == TOKEN_RIN && str[i] == '<' && ++i)
		type = TOKEN_HEREDOC;
	else if (type == TOKEN_ROUT && str[i] == '>' && ++i)
		type = TOKEN_APPEND;
	
	while (str[i] && ft_isspace(str[i]))
		i++;
	token = sub_token(ctrl, str + i, &i, (type != TOKEN_HEREDOC));
	if (!token)
		return (-1);
	if (cmd->status == -1)
	{
		free(token);
		return (i);
	}
	if (type == TOKEN_RIN)
	{
		if (access(token, R_OK))
		{
			token_error(token, 0);
			cmd->status = -1;
		}
		cmd->in.type = IO_INFILE;
		cmd->in.file.path = token;
	}
	else if (type == TOKEN_HEREDOC)
		cmd->in.type = IO_HEREDOC;
	else if (type == TOKEN_ROUT || type == TOKEN_APPEND)
	{
		if (cmd->out.fd > 0)
			close(cmd->out.fd);
		if (type == TOKEN_ROUT)
			cmd->out.fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->out.fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out.fd == -1)
		{
			token_error(token, 0);
			cmd->status = -1;
		}
		cmd->out.type = IO_OUTFILE;
		cmd->out.file.path = token;
		cmd->out.file.append = (type == TOKEN_APPEND);
	}
	errno = 0;
	return (i);
}
