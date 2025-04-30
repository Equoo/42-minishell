/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 01:08:31 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	bool		end;
}	t_ctrl;

int		load_ctrl(t_ctrl *ctrl, char **env);

int		execute_pipeline(t_ctrl *ctrl);


t_command	create_cmd(char *str);

short	ft_atos(char *str);
bool	check_ascii(char *str);

bool	set_signal(t_ctrl *ctrl);

void	free_node(t_env *node);
void	free_lst(t_env *lst);
void	ft_readline(t_ctrl *ctrl);

#endif
