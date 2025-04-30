/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:32:45 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 04:54:30 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_export_no_arg(t_env *lst)
{
	char	**table;
	char	*save;
	size_t	ct;
	size_t	ct_sort;

	ct_sort = 0;
	table = lst_to_tab(lst);
	if (table == NULL)
		return (false);
	while (ct_sort < ft_lstlen(lst) - 1)
	{
		ct = 0;
		while (ct < ft_lstlen(lst) - 1)
		{
			if (ft_strcmp(table[ct], table[ct + 1]) > 0)
			{
				save = table[ct];
				table[ct] = table[ct + 1];
				table[ct + 1] = save;
			}
			++ct;
		}
		++ct_sort;
	}
	print_export(table);
	return (true);
}

void	print_export(char **table)
{
	size_t	ct;

	ct = 0;
	while (table[ct] != NULL)
	{
		ft_putstr("declare -x ");
		ft_putstr(table[ct]);
		ft_putchar('\n');
		++ct;
	}
}

bool	ft_export(t_env *lst, char *key, char *val)
{
	t_env	*cpy;
	bool	check;

	cpy = lst;
	check = false;
	if (cpy == NULL)
		if (add_node_env(lst, ft_strdup(key), ft_strdup(val)) == false)
			return (false);
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->key, key) == 0)
		{
			free(cpy->value);
			cpy->value = val;
			check = true;
		}
		cpy = cpy->next;
	}
	if (check == false)
		if (add_node_env(lst, ft_strdup(key), ft_strdup(val)) == false)
			return (false);
	return (true);
}

bool	add_node_env(t_env *lst, char *key, char *val)
{
	t_env	*cpy;
	t_env	*node;
	
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (false);
	node->next = NULL;
	node->key = key;
	node->value = val;
	cpy = lst;
	if (cpy == NULL)
		*lst = *node;
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = node;
	return (true);
}
