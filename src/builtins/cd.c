/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 18:00:33 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "minishell.h"

static char	*get_path_env(t_env *lst, char *to_find)
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


bool	ft_cd(t_ctrl *ctrl, char *path)
{
	char	*buffer;

	buffer = get_path_env(ctrl->environ, "PWD");
	if (chdir(path) == -1)
		return (false);
	else
	{
		ft_export(ctrl->environ, "OLDPWD", buffer);
		ft_export(ctrl->environ, "PWD", getcwd(NULL, 0));
		return (true);
	}
	return (false);
}
