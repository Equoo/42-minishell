/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:23:22 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 16:43:51 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <stdlib.h>
#include "minishell.h"
#include "ft_printf.h"
#include "builtin.h"

int	ft_unset(t_ctrl *ctrl, char **flag, int fd)
{
	t_env	*cpy;
	t_env	*del;
	int		secure;

	(void) fd;
	cpy = ctrl->environ;
	secure = ft_unset_secure(ctrl, cpy, flag);
	if (secure != 1)
		return (secure);
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->next->key, flag[1]) == 0)
		{
			del = cpy->next;
			cpy->next = del->next;
			free_env(del);
			return (0);
		}
		cpy = cpy->next;
	}
	return (-1);
}

int	ft_unset_secure(t_ctrl *ctrl, t_env *cpy, char **flag)
{
	t_env	*del;

	if (cpy == NULL)
		return (-1);
	if (flag[1] == NULL)
	{
		ft_dprintf(STDERR_FILENO, "No Arg for Unset\n");
		return (-1);
	}
	if (ft_strcmp(cpy->key, flag[1]) == 0)
	{
		del = cpy;
		ctrl->environ = del->next;
		free_env(del);
		return (0);
	}
	return (1);
}

void	free_env(t_env *node)
{
	if (node == NULL)
		return ;
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}
