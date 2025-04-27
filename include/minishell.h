/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/27 23:05:03 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

extern	short	g_sigval;

typedef enum	e_flag
{
	F_PIPE,
	F_REDIR,
	F_HEREDOC
}	t_flag;

typedef struct s_pipe
{
	int		fd;
}	t_pipe;

typedef struct s_rdir
{
	int 	fd;	
	bool	append;
	char	*path;
}	t_rdir;

typedef struct s_heredoc
{
	int 	fd;
	int		tmpfd;
	char	*tmpfile;
	char	*end;
}	t_heredoc;

typedef struct s_inout
{
	t_flag	type;
	union
	{
		t_pipe pipe;
		t_rdir rdir;
		t_heredoc heredoc;
	};
}	t_inout;


typedef	struct	s_command
{
	char	*binary;
	char	**args;
	t_inout	in;
	t_inout	out;
}	t_command;

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_ctrl
{
	t_env		*environ;
	t_vector	commands;
	short		exit;
}	t_ctrl;

#endif