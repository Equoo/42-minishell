/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:38:28 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:36:43 by ticasali         ###   ########.fr       */
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

bool	ft_export_no_arg(t_env *lst);
bool	ft_export_exec(t_ctrl *ctrl, char *key, char *val);
void	print_export(char **table);

bool	secure_export(char *key);
bool	replace_node(t_env *node, char *new_value);

#endif