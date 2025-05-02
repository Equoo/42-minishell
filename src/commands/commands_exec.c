/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:22:53 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 18:43:59 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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

static int	test_builtins(t_ctrl *ctrl, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args[1], STDOUT_FILENO, 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(ctrl, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(STDOUT_FILENO);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(ctrl->environ, cmd->args[1], cmd->args[2]);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(ctrl->environ, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(ctrl->environ);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(ctrl, cmd->args[1]);
	else
		return (0);
	return (1);
}

static int	get_binary_path(t_ctrl *ctrl, t_command *cmd)
{
	char		*path;

	if (ft_strchr(cmd->args[0], '/'))
		return (0);
	if (test_builtins(ctrl, cmd))
		return (1);
	path = get_path(ctrl->environ, cmd->args[0]);
	if (path)
		cmd->args[0] = path;
	else
	{
		if (errno)
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd->args[0], strerror(errno));
		else
		 	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->args[0]);
		return (1);
	}
	return (0);
}

int	command_exec(void *ctrl, int i)
{
	t_command	*cmd;
	pid_t		child;
	int			status;

	cmd = ((t_ctrl *)ctrl)->commands.array + i;

	if (get_binary_path(ctrl, cmd))
		return (1);

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
