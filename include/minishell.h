/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 08:46:26 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "commands.h"
# include "environ.h"
# include "ft_vector.h"
# include <stdbool.h>
# include <unistd.h>

# define VERBOSE 0

extern volatile short	g_sigval;

typedef struct s_ctrl
{
	t_env				*environ;
	t_commands			commands;
	t_vector			heredocs;
	short				exit;
	bool				end;
	int					close_in;
	int					close_out;
}						t_ctrl;

typedef int				(*t_builtin)(t_ctrl *ctrl, char **args, int fd);

int						load_ctrl(t_ctrl *ctrl, char **env);
bool					set_signal(int check);
void					free_ctrl(t_ctrl *ctrl);

int						execute_pipeline(t_ctrl *ctrl);

short					ft_atos(char *str);
bool					check_ascii(char *str);

void					free_node(t_env *node);
void					free_lst(t_env *lst);
void					ft_readline(t_ctrl *ctrl);
void					redir_fds(t_ctrl *ctrl, t_command *cmd);
int						generate_tmp_name(u_char *str, size_t len);
void					anihilate_heredocs(t_vector *vec);

int						each_heredocs(t_ctrl *ctrl);
int						exit_commands(t_ctrl *ctrl, int status);

#endif
