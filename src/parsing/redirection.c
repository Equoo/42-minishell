/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:57:50 by ticasali         ###   ########.fr       */
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

static t_token_type	get_redir_type(char *str, size_t *i)
{
	t_token_type	type;

	type = TOKEN_NONE;
	if (str[*i] == '<' && ++(*i))
		type = TOKEN_RIN;
	else if (str[*i] == '>' && ++(*i))
		type = TOKEN_ROUT;
	if (type == TOKEN_RIN && str[*i] == '<' && ++(*i))
		type = TOKEN_HEREDOC;
	else if (type == TOKEN_ROUT && str[*i] == '>' && ++(*i))
		type = TOKEN_APPEND;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (type);
}

static void	set_cmd_outfile(t_command *cmd, char *token, t_token_type type)
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
	errno = 0;
}

static void	set_cmd_infile(t_command *cmd, char *token)
{
	if (access(token, R_OK))
	{
		token_error(token, 0);
		cmd->status = -1;
	}
	cmd->in.type = IO_INFILE;
	cmd->in.file.path = token;
	errno = 0;
}

static void	set_cmd_heredoc(t_command *cmd, char *token)
{
	cmd->in.type = IO_HEREDOC;
	cmd->in.heredoc.end = token;
}

int	parse_redirection(t_ctrl *ctrl, char *str, t_command *cmd)
{
	t_token_type	type;
	char			*token;
	size_t			i;

	i = 0;
	type = get_redir_type(str, &i);
	token = sub_token(ctrl, str + i, &i, (type != TOKEN_HEREDOC));
	if (!token)
		return (-1);
	if (cmd->status == -1)
	{
		free(token);
		return (i);
	}
	if (type == TOKEN_RIN)
		set_cmd_infile(cmd, token);
	else if (type == TOKEN_HEREDOC)
		set_cmd_heredoc(cmd, token);
	else if (type == TOKEN_ROUT || type == TOKEN_APPEND)
		set_cmd_outfile(cmd, token, type);
	return (i);
}
