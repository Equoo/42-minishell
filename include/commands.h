/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:53:34 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 22:56:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "environ.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

# define TMPFILE_LEN 37

typedef enum e_inout_type
{
	IO_NONE = 0,
	IO_PIPE = 1,
	IO_INFILE = 1 << 1,
	IO_OUTFILE = 1 << 2,
	IO_HEREDOC = 1 << 3,
}					t_inout_type;

typedef struct s_filerdir
{
	bool			append;
	char			*path;
}					t_filerdir;

typedef struct s_heredoc
{
	char			tmpfile[TMPFILE_LEN];
	char			*end;
}					t_heredoc;

typedef struct s_inout
{
	t_inout_type	type;
	int				fd;
	union
	{
		t_filerdir	file;
		t_heredoc	heredoc;
	};
}					t_inout;

typedef struct s_command
{
	char			*binary;
	char			**args;
	t_inout			in;
	t_inout			out;
	pid_t			pid;
	int				status;
}					t_command;

typedef struct s_commands
{
	t_command		*array;
	size_t			size;
	size_t			len;
}					t_commands;

char				*get_path(t_env *lst, char *command);

t_commands			commands_init(size_t size);
int					commands_append(t_commands *cmds, t_command cmd);
void				commands_destroy(t_commands *cmds);

void				commands_close_fds(t_commands cmds);
int					open_file(char *path, int flags);
int					open_pipe(t_inout *in_pipe, t_inout *out_pipe);

int					command_exec(void *ctrl, int i);

#endif
