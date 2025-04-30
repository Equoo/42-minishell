/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:23:22 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 04:52:38 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env *lst, char *key)
{
	t_env	*cpy;
	t_env	*del;

	cpy = lst;
	if (cpy == NULL)
		return ;
	if (ft_strcmp(cpy->key, key) == 0)
	{
		del = cpy;
		*lst = *del->next;
		free_node(del);
	}
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->next->key, key) == 0)
		{
			del = cpy->next;
			cpy->next = del->next;
			free_node(del);
			return ;
		}
		cpy = cpy->next;
	}
}

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}