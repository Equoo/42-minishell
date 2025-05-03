/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 18:12:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

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

int	create_temp_file(char *tmp_file)
{
	int		fd;

	ft_strlcpy(tmp_file, "/tmp/", 6);
	if (generate_tmp_name((u_char *)(tmp_file + 5), TMPFILE_LEN - 5))
		return (-1);
	while (access(tmp_file, F_OK) == 0)
		if (generate_tmp_name((u_char *)(tmp_file + 5), TMPFILE_LEN - 5))
			return (-1);
	fd = open(tmp_file, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
	{
		perror("Minishell: Failed to create temporary file");
		return (-1);
	}
	return (fd);
}
// if LIMITER in quotes, don't expand

//static int	do_heredoc(t_ctrl *ctrl, t_command *cmd)
//{
//	char	*input;
//	char	*expanded;
//	int		fd;

//	fd = create_temp_file(cmd->in.heredoc.tmpfile);
//	if (fd == -1)
//		return (0);
//	while (1)
//	{
//		input = readline(">");
//		if (!input)
//			break ;
//		if (ft_strcmp(input, cmd->in.heredoc.end) == 0)
//		{
//			free(input);
//			break ;
//		}
//		expanded = expand_all(ctrl, input);
//		if (!expanded)
//		{
//			free(input);
//			close(fd);
//			unlink(cmd->in.heredoc.tmpfile);
//			return (1);
//		}
//		expanded = ft_strjoin(expanded, "\n");
//		write(fd, expanded, ft_strlen(expanded));
//		free(input);
//	}
//	return (0);
//}

//static int	execute_heredocs(t_ctrl *ctrl)
//{
//	t_command	*cmd;
//	size_t		i;

//	i = 0;
//	while (i < ctrl->commands.len)
//	{
//		cmd = &ctrl->commands.array[i];
//		if (cmd->in.type == IO_HEREDOC)
//			if (do_heredoc(ctrl, cmd))
//				return (0);
//		i++;
//	}
//	return (1);
//}

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
			if (parse_command(ctrl, input) /*&& execute_heredocs(ctrl)*/)
				if (execute_pipeline(ctrl) && errno)
					ctrl->end = true;
		commands_destroy(&ctrl->commands);
		free(input);
	}
}
