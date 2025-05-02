/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:38:28 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 18:56:51 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int	ft_export(t_ctrl *ctrl, char **flag);
int	ft_cd(t_ctrl *ctrl, char **flag);
int	ft_unset(t_env *lst, char *key);
int	ft_env(t_ctrl *ctrl, char **flag);
int	ft_pwd(t_ctrl *ctrl, char **flag);
int	ft_echo(t_ctrl *ctrl, char **flag);
int	ft_exit(t_ctrl *ctrl, char *val);

bool	ft_export_no_arg(t_env *lst);
void	print_export(char **table);

#endif