/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 17:16:18 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

bool	ft_cd(t_ctrl *ctrl, char *path)
{
	char	*buffer;
	char	*new_pwd;

	buffer = get_path_env(ctrl->environ, "PWD");
	if (chdir(path) == -1)
		return (false);
	else
	{
		ft_export(ctrl->environ, "OLDPWD", buffer);
		ft_export(ctrl->environ, "PWD", ft_strdup(getcwd(new_pwd, 4096)));
		return (true);
	}
	return (false);
}

char	*get_path_env(t_env *lst, char *to_find)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (ft_strcmp(lst->key, to_find) == 0)
			return (lst->value);
		cpy = cpy->next;
	}
	return (NULL);
}
