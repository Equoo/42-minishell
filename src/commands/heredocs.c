/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:25:03 by dderny            #+#    #+#             */
/*   Updated: 2025/05/05 08:34:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_printf.h"
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
#include <sys/wait.h>
#include <unistd.h>

int	generate_tmp_name(u_char *str, size_t len)
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

	errno = 0;
	fd = open(tmp_file, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
	{
		perror("minishell: Failed to create temporary file");
		return (-1);
	}
	return (fd);
}

static int	heredoc_getline(t_ctrl *ctrl, t_heredoc *hd, int fd)
{
	char	*input;
	char	*expanded;

	set_signal(2);
	input = readline(">");
	if (!input || errno)
		return (1);
	set_signal(0);
	if (ft_strcmp(input, hd->end) == 0 || g_sigval == 2)
	{
		free(input);
		return (1);
	}
	if (!hd->expand)
		expanded = heredoc_expand(ctrl, input, false);
	else
		expanded = input;
	if (expanded)
		ft_dprintf(fd, "%s\n", expanded);
	if (!hd->expand)
		free(expanded);
	if (input)
		free(input);
	return (0);
}

static int	do_heredoc(t_ctrl *ctrl, t_heredoc *hd, int *status)
{
	pid_t		child;
	int			fd;

	fd = create_temp_file(hd->tmpfile);
	if (fd == -1)
		return (1);
	child = fork();
	if (child && (!errno || ft_dprintf(STDERR_FILENO,
				"minishell: heredoc, %s\n", strerror(errno))))
	{
		if (child)
			waitpid(child, status, 0);
		close(fd);
		return (errno);
	}
	while (!errno)
		if (heredoc_getline(ctrl, hd, fd))
			break ;
	close(fd);
	if (g_sigval)
		unlink(hd->tmpfile);
	commands_close_fds(ctrl->commands);
	exit_commands(ctrl, g_sigval);
	return (0);
}

int	each_heredocs(t_ctrl *ctrl)
{
	t_heredoc	*hd;
	ssize_t		i;
	int			status;

	i = 0;
	status = 0;
	while (i < ctrl->heredocs.actual_size && WEXITSTATUS(status) != 2)
	{
		hd = &((t_heredoc *)ctrl->heredocs.data)[i];
		if (hd->end == NULL)
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: heredoc: no end delimiter\n");
			return (0);
		}
		if (do_heredoc(ctrl, hd, &status))
			return (0);
		if (WEXITSTATUS(status) == 2)
			ctrl->exit = 130;
		if (WEXITSTATUS(status) == 2)
			return (0);
		i++;
	}
	return (1);
}
