/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 03:48:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "minishell.h"
#include "ft_printf.h"
#include <errno.h>
#include <string.h>

bool	ft_export_cd(t_ctrl *ctrl, char *key, char *val, bool check)
{
	t_env	*cpy;

	if (!val)
		return (true);
	cpy = ctrl->environ;
	if (secure_export(key) == false)
		return (false);
	if (cpy == NULL)
	{
		if (add_node_env(&ctrl->environ, key, val) == false)
			return (false);
		return (true);
	}
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->key, key) == 0)
			check = replace_node(cpy, key, val);
		cpy = cpy->next;
	}
	if (ft_strcmp(cpy->key, key) == 0)
		check = replace_node(cpy, key, val);
	if (check == false)
		if (add_node_env(&ctrl->environ, key, val) == false)
			return (false);
	return (true);
}

char	*get_path_env(t_env *lst, char *to_find)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (ft_strcmp(cpy->key, to_find) == 0)
			return (cpy->value);
		cpy = cpy->next;
	}
	return (NULL);
}

int	ft_cd(t_ctrl *ctrl, char **flag, int fd)
{
	char	*buffer;

	(void) fd;
	buffer = get_path_env(ctrl->environ, "PWD");
	if (flag[1] == NULL)
		return (ft_cd_no_arg(ctrl, buffer));
	if (chdir(flag[1]) == -1)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: cd: %s: %s\n", flag[1], strerror(errno));
		return (1);
	}
	else
	{
		if (buffer != NULL)
			ft_export_cd(ctrl, ft_strdup("OLDPWD"), ft_strdup(buffer), false);
		buffer = getcwd(NULL, 0);
		if (buffer)
			ft_export_cd(ctrl, ft_strdup("PWD"), buffer, false);
		if (errno)
			ft_dprintf(STDERR_FILENO, "minishell: cd: %s\n", strerror(errno));
		return (errno);
	}
	return (1);
}

int	ft_cd_no_arg(t_ctrl *ctrl, char *buffer)
{
	if (get_path_env(ctrl->environ, "HOME") == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(get_path_env(ctrl->environ, "HOME")) == -1)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: cd: %s: %s\n",
			get_path_env(ctrl->environ, "HOME"), strerror(errno));
		return (1);
	}
	if (buffer != NULL)
		ft_export_cd(ctrl, ft_strdup("OLDPWD"), ft_strdup(buffer), false);
	buffer = getcwd(NULL, 0);
	if (buffer)
		ft_export_cd(ctrl, ft_strdup("PWD"), buffer, false);
	if (errno)
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s\n", strerror(errno));
	return (errno);
}
