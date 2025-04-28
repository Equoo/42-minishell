/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:32:06 by dderny            #+#    #+#             */
/*   Updated: 2025/04/28 09:02:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "commands.h"
#include "ft_printf.h"
#include <errno.h>
#include <libft.h>
#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


int	main(int argc, char **argv, char **env)
{
	t_commands cmds;

	(void)env;
	if (argc < 7)
	{
		fprintf(stderr, "Usage: %s <command> [args]\n", argv[0]);
		return (1);
	}
	cmds = commands_init(8);
	if (!cmds.array)
	{
		fprintf(stderr, "Failed to initialize commands\n");
		return (1);
	}

	char	*in_file = argv[1];
	char	*out_file = argv[argc - 1];
	int	i;
	i = 2;
	while (i < argc - 1)
	{
		t_command	cmd = {.in.fd = -1, .out.fd = -1, .binary = NULL, .args = NULL};
		cmd.binary = ft_strdup(argv[i]);
		cmd.args = (char **)malloc(sizeof(char *) * (*argv[i + 1] ? 3 : 2));
		if (!cmd.binary || !cmd.args)
		{
			fprintf(stderr, "Failed to allocate memory for command\n");
			commands_destroy(&cmds);
			return (1);
		}
		cmd.args[0] = cmd.binary;
		if (*argv[i + 1])
		{
			cmd.args[1] = argv[i + 1];
			cmd.args[2] = NULL;
		}
		else
			cmd.args[1] = NULL;
		if (i == 2)
		{
			cmd.in.file.path = in_file;
			cmd.in.type = IO_INFILE;
		}
		else
			cmd.in.type = IO_PIPE;
		if (i == argc - 3)
		{
			cmd.out.type = IO_OUTFILE;
			cmd.out.file.path = out_file;
		}
		else
		{
			cmd.out.pipeout = (i - 2) / 2 + 1;
			cmd.out.type = IO_PIPE;
		}
		if (commands_append(&cmds, cmd))
		{
			fprintf(stderr, "Failed to append command\n");
			free(cmd.binary);
			free(cmd.args);
			commands_destroy(&cmds);
			return (1);
		}
		i += 2;
	}

	size_t j = 0;
	while (j < cmds.len)
	{
		errno = 0;
		if (cmds.array[j].in.type & IO_INFILE)
			cmds.array[j].in.fd = open_file(cmds.array[j].in.file.path, O_RDONLY);
		if (cmds.array[j].out.type & IO_OUTFILE && cmds.array[j].out.file.append)
			cmds.array[j].out.fd = open_file(cmds.array[j].out.file.path, O_WRONLY | O_CREAT | O_APPEND);
		else if (cmds.array[j].out.type & IO_OUTFILE)
			cmds.array[j].out.fd = open_file(cmds.array[j].out.file.path, O_WRONLY | O_CREAT | O_TRUNC);
		if (cmds.array[j].out.type & IO_PIPE && cmds.array[j].out.pipeout < cmds.len && cmds.array[cmds.array[j].out.pipeout].in.type == IO_PIPE)
			open_pipe(&cmds.array[j].out, &cmds.array[cmds.array[j].out.pipeout].in);
		if (command_exec(cmds, j, env) + 1)
			return (1);
		j++;
	}
	commands_close_fds(cmds);
	j = -1;
	while (++j < cmds.len)
	{
		if (!cmds.array[j].binary || !cmds.array[j].args)
			continue ;
		if (cmds.array[j].pid != -1)
			waitpid(cmds.array[j].pid, &cmds.array[j].status, 0);
		printf("%s exit with status: %d\n", cmds.array[j].binary, cmds.array[j].status);
	}

	int status = cmds.array[cmds.len - 1].status;
	commands_destroy(&cmds);
	return (status);
}
