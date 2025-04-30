/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:47:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 18:06:31 by ticasali         ###   ########.fr       */
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
	bool		end;
}	t_ctrl;

t_ctrl	*load_ctrl(t_ctrl *ctrl, char **env);

t_env	*lst_init(char **env);

t_commands	parsing(char *str);
t_command	create_cmd(char *str);

char	**lst_to_tab(t_env *lst);
char	**ft_quote_split(char *str, char c);

char	*ft_strdup(char *str);
char	*ft_strdup_select(char *str, char c);
char	*concat_env(char *key, char *val);
char	*expand_env(t_env *lst, char *to_find);
char	*remove_quote(char *str);
char	*ft_strdup_quote(char *str, char c);

void	*free_table(char **table);
void	*ft_free_split(char **tab);

size_t	ft_strlen(char *str);
size_t	ft_tablen(char **table);
size_t	ft_strlen_select(char *str, char c);
size_t	ft_lstlen(t_env *lst);
size_t	count_pipe(char *str, char c);

int		ft_strcmp(char *s1, char *s2);

short	ft_atos(char *str);

bool	add_node(t_env **lst, char *env, size_t ct);
bool	set_node_val(t_env *node, char *env);
bool	ft_export_no_arg(t_env *lst);
bool	ft_export(t_env *lst, char *key, char *val);
bool	add_node_env(t_env *lst, char *key, char *val);
bool	ft_cd(t_ctrl *ctrl, char *path);
bool	check_parsing(char	*str);
bool	check_end_command(char *str);
bool	check_single_quote(char *str);
bool	check_double_quote(char *str);
bool	check_quote_combine(char *str);
bool	check_ascii(char *str);
bool	set_signal(t_ctrl *ctrl);

void	ft_env(t_env *lst);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_unset(t_env *lst, char *key);
void	print_export(char **table);
void	free_node(t_env *node);
void	ft_echo(char *str, int fd, bool	flag);
void	ft_exit(t_ctrl *ctrl, char *val);
void	free_lst(t_env *lst);
void	ft_pwd(int fd);
void	ft_readline(t_ctrl *ctrl);

#endif
