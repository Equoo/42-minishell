/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 06:30:55 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
//# include <stdbool.h>
//# include <dirent.h>
//# include <errno.h>
//# include <readline/history.h>
//# include <readline/readline.h>
//# include <signal.h>
//# include <stdlib.h>
//# include <sys/ioctl.h>
//# include <sys/resource.h>
//# include <sys/stat.h>
//# include <sys/types.h>
//# include <sys/wait.h>
//# include <term.h>
//# include <termcap.h>
//# include <termios.h>
//# include <unistd.h>

# include "commands.h"
# include "environ.h"
# include <stdbool.h>
# include <unistd.h>

# define VERBOSE 1

extern	short	g_sigval;

typedef struct	s_ctrl
{
	t_env		*environ;
	t_commands	commands;
	char		*last_pwd;
	char		*pwd;
	short		exit;
}	t_ctrl;

#endif
