/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 21:58:07 by dderny           ###   ########.fr       */
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

static t_token_type	get_redir_type(char *str)
{
	t_token_type	type;
	size_t			i;

	i = 0;
	type = TOKEN_NONE;
	if (str[i] == '<' && ++i)
		type = TOKEN_RIN;
	else if (str[i] == '>' && ++i)
		type = TOKEN_ROUT;
	if (type == TOKEN_RIN && str[i] == '<' && ++i)
		type = TOKEN_HEREDOC;
	else if (type == TOKEN_ROUT && str[i] == '>' && ++i)
		type = TOKEN_APPEND;
	if (str[i])
	{
		token_error(NULL, str[i]);
		return (TOKEN_NONE);
	}
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
		cmd->status = 1;
	}
	cmd->out.type = IO_OUTFILE;
	cmd->out.file.path = token;
	cmd->out.file.append = (type == TOKEN_APPEND);
	errno = 0;
}

static void	set_cmd_infile(t_command *cmd, char *token)
{
	if (!cmd->status && access(token, R_OK))
	{
		cmd->status = 1;
	}
	if (cmd->in.type == IO_PIPE)
		cmd->in.oldfd = cmd->in.fd;
	cmd->in.type = IO_INFILE;
	cmd->in.file.path = token;
	errno = 0;
}

static int	set_cmd_heredoc(t_command *cmd, char *limiter)
{
	cmd->in.type = IO_HEREDOC;
	cmd->in.heredoc.end = ft_strdup(limiter);
	return (0);
}

int	parse_redirection(t_ctrl *ctrl, t_vector array, ssize_t i,
	t_command *cmd)
{
	char			**chunks;
	t_token_type	type;
	char			*path;
	char			quotes[2];

	chunks = (char **)array.data;
	if (i + 1 >= array.actual_size /*|| ft_strchr("<>", chunks[i + 1][0])*/)
		return (-3);
	type = get_redir_type(chunks[i]);
	free(chunks[i]);
	ft_bzero(quotes, 2);
	if (type == TOKEN_HEREDOC)
		return (set_cmd_heredoc(cmd, chunks[i + 1]));
	if (cmd->status == -1 || type == TOKEN_NONE)
		return (-1);
	path = get_expanded(ctrl, chunks[i + 1], quotes);
	if (!path)
		return (-1);
	if (type == TOKEN_RIN)
		set_cmd_infile(cmd, path);
	else if (type == TOKEN_ROUT || type == TOKEN_APPEND)
		set_cmd_outfile(cmd, path, type);
	return (cmd->status);
}
