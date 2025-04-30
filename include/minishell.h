/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 04:49:35 by ticasali         ###   ########.fr       */
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

t_env	*lst_init(char **env);

char	**lst_to_tab(t_env *lst);

char	*ft_strdup(char *str);
char	*ft_strdup_select(char *str, char c);
char	*concat_env(char *key, char *val);

void	*free_table(char **table);

size_t	ft_strlen(char *str);
size_t	ft_tablen(char **table);
size_t	ft_strlen_select(char *str, char c);
size_t	ft_lstlen(t_env *lst);

int		ft_strcmp(char *s1, char *s2);

bool	add_node(t_env **lst, char *env, size_t ct);
bool	set_node_val(t_env *node, char *env);
bool	ft_export_no_arg(t_env *lst);
bool	ft_export(t_env *lst, char *key, char *val);
bool	add_node_env(t_env *lst, char *key, char *val);

void	ft_env(t_env *lst);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_unset(t_env *lst, char *key);
void	print_export(char **table);
void	free_node(t_env *node);

#endif
