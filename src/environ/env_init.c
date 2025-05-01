/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:41:42 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 08:09:37 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

t_env	*env_init(char **env)
{
	t_env	*lst;
	size_t	ct;

	ct = 0;
	lst = NULL;
	while (env[ct] != NULL)
	{
		if (add_env(&lst, env[ct], ct) == false)
		{
			free_envs(lst);
			return (NULL);
		}
		++ct;
	}
	return (lst);
}

bool	add_env(t_env **lst, char *env, size_t ct)
{
	t_env	*node;
	t_env	*cpy;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (false);
	if (set_env_val(node, env) == false)
	{
		free(node);
		return (false);
	}
	if (ct == 0)
	{
		*lst = node;
		return (true);
	}
	cpy = *lst;
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = node;
	return (true);
}

bool	set_env_val(t_env *node, char *env)
{
	size_t	ct;

	ct = 0;
	node->next = NULL;
	node->key = ft_strdup_select(env, '=');
	if (node->key == NULL)
		return (false);
	while (env[ct] != '\0' && env[ct] != '=')
		++ct;
	++ct;
	node->value = ft_strdup(&env[ct]);
	if (node->value == NULL)
	{
		free(node->key);
		return (false);
	}
	return (true);
}

void	free_envs(t_env *lst)
{
	t_env	*cpy;
	t_env	*del;

	cpy = lst;
	while (cpy != NULL)
	{
		del = cpy;
		cpy = cpy->next;
		free(del);
	}
}

size_t	ft_envslen(t_env *lst)
{
	size_t	ct;
	t_env	*cpy;

	ct = 0;
	cpy = lst;
	while (cpy != NULL)
	{
		cpy = cpy->next;
		++ct;
	}
	return (ct);
}
