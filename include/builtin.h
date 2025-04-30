/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:38:28 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 00:01:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

bool	ft_export_no_arg(t_env *lst);
bool	ft_export(t_env *lst, char *key, char *val);
bool	ft_cd(t_ctrl *ctrl, char *path);
void	ft_unset(t_env *lst, char *key);
void	ft_env(t_env *lst);
void	ft_pwd(int fd);
void	ft_echo(char *str, int fd, bool	flag);
void	ft_exit(t_ctrl *ctrl, char *val);
void	print_export(char **table);


#endif