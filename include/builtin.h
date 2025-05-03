/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:38:28 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 10:31:55 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int		ft_export(t_ctrl *ctrl, char **flag);
int		ft_cd(t_ctrl *ctrl, char **flag);
int		ft_unset(t_ctrl *ctrl, char **flag);
int		ft_env(t_ctrl *ctrl, char **flag);
int		ft_pwd(t_ctrl *ctrl, char **flag);
int		ft_echo(t_ctrl *ctrl, char **flag);
int		ft_exit(t_ctrl *ctrl, char **flag);

int		ft_unset_secure(t_ctrl *ctrl, t_env *cpy, char **flag);
int		ft_cd_no_arg(t_ctrl *ctrl, char *buffer);

bool	ft_export_no_arg(t_env *lst);
bool	ft_export_exec(t_ctrl *ctrl, char *key, char *val);
void	print_export(char **table);
void	print_var_export(char *str);

bool	secure_export(char *key);
bool	replace_node(t_env *node, char *new_key, char *new_value);
bool	ft_export_cd(t_ctrl *ctrl, char *key, char *val);
void	sort_table(t_env *lst, char **table);

#endif