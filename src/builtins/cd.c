/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 22:45:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "minishell.h"

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


int		ft_cd(t_ctrl *ctrl, char **flag)
{
	char	*buffer;

	buffer = get_path_env(ctrl->environ, "PWD");
	if (flag[1] == NULL)
	{
		if (chdir(get_path_env(ctrl->environ, "HOME")) == -1)
			return (-1);
		return (0);
	}
	if (chdir(flag[1]) == -1)
		return (-1);
	else
	{
		ft_export_exec(ctrl, ft_strdup("OLDPWD"), ft_strdup(buffer));
		ft_export_exec(ctrl, ft_strdup("PWD"), getcwd(NULL, 0));
		return (0);
	}
	return (-1);
}
