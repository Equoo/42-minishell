/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:22:53 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 18:11:53 by dderny           ###   ########.fr       */
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

static t_builtin	get_builtin(t_command *cmd)
{
	const char		built_names[][32] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	const t_builtin	built_funcs[] = {&ft_echo, &ft_cd, &ft_pwd,
		&ft_export, &ft_unset, &ft_env, &ft_exit};
	int				i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->args[0], built_names[i]) == 0)
			return (built_funcs[i]);
		i++;
	}
	return (NULL);
}

static int	get_binary_or_builtin(t_ctrl *ctrl,
	t_command *cmd, t_builtin *builtin_func)
{
	char		*path;

	*builtin_func = NULL;
	if (!ft_strchr(cmd->args[0], '/'))
	{
		*builtin_func = get_builtin(cmd);
		if (*builtin_func)
			return (0);
		path = get_path(ctrl->environ, cmd->args[0]);
		cmd->binary = path;
		if (!path)
		{
			if (errno)
				ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
					cmd->args[0], strerror(errno));
			else
			{
				ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
					cmd->args[0]);
				ctrl->exit = 127;
			}
			cmd->status = 1;
		}
	}
	return (0);
}

static int	exec_builtin(t_ctrl *ctrl, t_builtin builtin_func, t_command *cmd)
{
	int	status;

	if (cmd->out.type == IO_OUTFILE)
		status = builtin_func(ctrl, cmd->args, cmd->out.fd);
	else
		status = builtin_func(ctrl, cmd->args, STDOUT_FILENO);
	cmd->status = status;
	return (0);
}

static int	check_and_execute(t_command *cmd, t_env *envs)
{
	char		**environ;
	struct stat	info;

	if (errno)
		return (1);
	info = (struct stat){0};
	stat(cmd->args[0], &info);
	if (!cmd->binary && S_ISDIR(info.st_mode))
		return (print_error_exec(cmd->args[0], true));
	if (!cmd->binary && access(cmd->args[0], R_OK | X_OK))
		return (print_error_exec(cmd->args[0], false));
	environ = env_to_array(envs);
	if (!environ)
		return (1);
	if (cmd->binary)
		execve(cmd->binary, cmd->args, environ);
	else
		execve(cmd->args[0], cmd->args, environ);
	free(environ);
	return (1);
}

int	command_exec(void *ctrl, int i)
{
	t_command	*cmd;
	pid_t		child;
	t_builtin	builtin_func;

	cmd = ((t_ctrl *)ctrl)->commands.array + i;
	if (get_binary_or_builtin(ctrl, cmd, &builtin_func))
		return (1);
	if (builtin_func && cmd->out.type != IO_PIPE && cmd->in.type != IO_PIPE)
		return (exec_builtin(ctrl, builtin_func, cmd));
	child = fork();
	if (child)
	{
		cmd->pid = child;
		return (0);
	}
	redir_fds(cmd);
	commands_close_fds(((t_ctrl *)ctrl)->commands);
	if (builtin_func)
		cmd->status = exec_builtin(ctrl, builtin_func, cmd);
	else if (!cmd->status)
		cmd->status = check_and_execute(cmd, ((t_ctrl *)ctrl)->environ);
	return (exit_commands(ctrl, cmd->status));
}
