/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:32:45 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 20:25:31 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"


static void	print_export(char **table)
{
	size_t	ct;

	ct = 0;
	while (table[ct] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(table[ct], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		++ct;
	}
}

bool	ft_export_no_arg(t_env *lst)
{
	char	**table;
	char	*save;
	size_t	ct;
	size_t	ct_sort;

	ct_sort = 0;
	table = env_to_array(lst);
	if (table == NULL)
		return (false);
	while (ct_sort < ft_envslen(lst) - 1)
	{
		ct = 0;
		while (ct < ft_envslen(lst) - 1)
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

bool	ft_export_exec(t_ctrl *ctrl, char *key, char *val)
{
	t_env	*cpy;
	bool	check;

	cpy = ctrl->environ;
	check = false;
	if (cpy == NULL)
		if (add_node_env(ctrl->environ, key, val) == false)
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
		if (add_node_env(ctrl->environ, key, val) == false)
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

int	ft_export(t_ctrl *ctrl, char **flag)
{
	char	*key;
	char	*val;
	size_t	ct;

	ct = 0;
	if (flag[1] == NULL)
		ft_export_no_arg(ctrl->environ);
	key = ft_strdup_select(flag[1], '=');
	while (flag[1][ct] != '\0' && flag[1][ct] != '=')
		++ct;
	if (flag[1][ct] == '\0')
		val = NULL;
	else if (flag[1][ct + 1] == '\0')
		val = ft_calloc(sizeof(char), 1);
	else
		val = ft_strdup(&flag[1][ct + 1]);
	if (ft_export_exec(ctrl, key, val) == true)
		return (0);
	else
		return (-1);
}