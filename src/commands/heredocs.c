/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:25:03 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 23:37:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int	generate_tmp_name(u_char *str, size_t len)
{
	int		rand_fd;
	size_t	i;

	rand_fd = open("/dev/urandom", O_RDONLY);
	if (rand_fd == -1)
		return (1);
	if (read(rand_fd, str, len - 1) == -1)
	{
		close(rand_fd);
		return (1);
	}
	close(rand_fd);
	i = -1;
	while (++i < len - 1)
		str[i] = 48 + str[i] % (127 - 48);
	str[len - 1] = '\0';
	return (0);
}

static int	create_temp_file(char *tmp_file)
{
	int		fd;

	ft_strlcpy(tmp_file, "/tmp/", 6);
	if (generate_tmp_name((u_char *)(tmp_file + 5), TMPFILE_LEN - 5))
		return (-1);
	while (access(tmp_file, F_OK) == 0)
		if (generate_tmp_name((u_char *)(tmp_file + 5), TMPFILE_LEN - 5))
			return (-1);
	errno = 0;
	fd = open(tmp_file, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
	{
		perror("minishell: Failed to create temporary file");
		return (-1);
	}
	return (fd);
}

static int	do_heredoc(t_ctrl *ctrl, t_command *cmd)
{
	char	*input;
	char	*expanded;
	int		fd;

	fd = create_temp_file(cmd->in.heredoc.tmpfile);
	if (fd == -1)
		return (0);
	while (!errno)
	{
		input = readline(">");
		if (!input || errno)
			break ;
		if (ft_strcmp(input, cmd->in.heredoc.end) == 0)
		{
			free(input);
			break ;
		}
		expanded = heredoc_expand(ctrl, input);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
			free(expanded);
		}
		free(input);
	}
	close(fd);
	if (errno)
		unlink(cmd->in.heredoc.tmpfile);
	return (0);
}

int	execute_heredocs(t_ctrl *ctrl)
{
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < ctrl->commands.len)
	{
		cmd = &ctrl->commands.array[i];
		if (cmd->in.type == IO_HEREDOC)
		{
			if (cmd->in.heredoc.end == NULL)
			{
				dprintf(STDERR_FILENO, "minishell: heredoc: no end delimiter\n");
				return (0);
			}
			if (do_heredoc(ctrl, cmd))
				return (0);
		}
		i++;
	}
	return (1);
}
