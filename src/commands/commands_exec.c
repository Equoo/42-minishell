/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:22:53 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 14:57:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <libft.h>
#include <unistd.h>

static void	open_fds(t_command *cmd)
{
	if (cmd->in.type && (!cmd->in.fd || cmd->in.fd == -1))
		cmd->in.fd = open_file("/dev/null", O_RDONLY);
	if (!errno && cmd->in.type)
		dup2(cmd->in.fd, STDIN_FILENO);
	if (!errno && cmd->out.type && (!cmd->out.fd || cmd->out.fd == -1))
		open_file("/dev/null", O_WRONLY | O_CREAT | O_TRUNC);
	if (!errno && cmd->out.type)
		dup2(cmd->out.fd, STDOUT_FILENO);
}

static int	check_and_execute(t_command *cmd, t_env *envs)
{
	char		**environ;
	struct stat	info;

	if (errno || !cmd->args || !cmd->args[0])
		return (errno);
	info = (struct stat){0};
	stat(cmd->args[0], &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: is a directory\n", cmd->args[0]);
		return (126);
	}
	if (access(cmd->args[0], R_OK | X_OK))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd->args[0], strerror(errno));
		return (127);
	}
	environ = env_to_array(envs);
	if (!environ)
		return (errno);
	execve(cmd->args[0], cmd->args, environ);
	free(environ);
	return (0);
}

int	command_exec(void *ctrl, int i)
{
	t_command	*cmd;
	pid_t		child;
	int			status;

	cmd = ((t_ctrl *)ctrl)->commands.array + i;
	// for binary without /
	// 		check if is builtin
	// 		search in PATH for the binary
	child = fork();
	if (child)
	{
		cmd->pid = child;
		return (-1);
	}
	if (VERBOSE)
		ft_printf("%s: in %d out %d\n", cmd->args[0], cmd->in.type ? cmd->in.fd :
			-1, cmd->out.type ? cmd->out.fd : -1);
	open_fds(cmd);
	commands_close_fds(((t_ctrl *)ctrl)->commands);
	status = check_and_execute(cmd, ((t_ctrl *)ctrl)->environ);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_ctrl(ctrl);
	exit(status);
	return (0);
}
