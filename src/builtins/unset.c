/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:23:22 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 18:55:01 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

int	ft_unset(t_ctrl *ctrl, char **flag)
{
	t_env	*cpy;
	t_env	*del;

	cpy = ctrl->environ;
	if (cpy == NULL)
		return ;
	if (ft_strcmp(cpy->key, flag[1]) == 0)
	{
		del = cpy;
		*ctrl->environ = *del->next;
		free_env(del);
	}
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->next->key, flag[1]) == 0)
		{
			del = cpy->next;
			cpy->next = del->next;
			free_env(del);
			return ;
		}
		cpy = cpy->next;
	}
}

void	free_env(t_env *node)
{
	if (node == NULL)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}
