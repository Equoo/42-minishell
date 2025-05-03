/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 22:42:08 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "commands.h"
# include "environ.h"
# include <stdbool.h>
# include <unistd.h>

# define VERBOSE 0

extern short	g_sigval;

typedef struct s_ctrl
{
	t_env		*environ;
	t_commands	commands;
	short		exit;
	bool		end;
}	t_ctrl;

typedef int		(*t_builtin)(t_ctrl *ctrl, char **args, int fd);

int				load_ctrl(t_ctrl *ctrl, char **env);
bool			set_signal(void);
void			free_ctrl(t_ctrl *ctrl);

int				execute_pipeline(t_ctrl *ctrl);

t_command		create_cmd(char *str);

short			ft_atos(char *str);
bool			check_ascii(char *str);

void			free_node(t_env *node);
void			free_lst(t_env *lst);
void			ft_readline(t_ctrl *ctrl);

int				execute_heredocs(t_ctrl *ctrl);\

#endif
