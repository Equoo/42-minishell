/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:32:45 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 13:16:18 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <errno.h>
#include <libft.h>
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "builtin.h"

bool	ft_export_no_arg(t_env *lst, int fd)
{
	char	**table;
	size_t	ct_sort;

	ct_sort = -1;
	table = env_to_array(lst);
	if (table == NULL)
		return (false);
	while (++ct_sort < ft_envslen(lst) - 1)
		sort_table(lst, table);
	print_export(table, fd);
	ft_freearray((void **)table);
	return (true);
}

bool	ft_export_exec(t_ctrl *ctrl, char *key, char *val)
{
	t_env	*cpy;
	bool	check;

	cpy = ctrl->environ;
	check = false;
	if (secure_export(key) == false)
		return (false);
	if (cpy == NULL)
		if (add_node_env(ctrl->environ, key, val) == false)
			return (false);
	while (cpy->next != NULL)
	{
		if (ft_strcmp(cpy->key, key) == 0)
			check = replace_node(cpy, key, val);
		cpy = cpy->next;
	}
	if (ft_strcmp(cpy->key, key) == 0)
		check = replace_node(cpy, key, val);
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

static int	parse_n_export(t_ctrl *ctrl, char *flag)
{
	char	*key;
	char	*val;
	size_t	ct;

	ct = 0;
	key = ft_strdup_select(flag, '=');
	if (key == NULL)
		return (1);
	while (flag[ct] != '\0' && flag[ct] != '=')
		++ct;
	if (flag[ct] == '\0')
		val = NULL;
	else if (flag[ct + 1] == '\0')
		val = ft_calloc(sizeof(char), 1);
	else
		val = ft_strdup(&flag[ct + 1]);
	if (ft_export_exec(ctrl, key, val) == true)
		return (0);
	else
	{
		free(key);
		free(val);
		return (1);
	}
}

int	ft_export(t_ctrl *ctrl, char **flag, int fd)
{
	int	status;

	status = 0;
	if (flag[1] == NULL)
	{
		ft_export_no_arg(ctrl->environ, fd);
		return (0);
	}
	while (*flag)
	{
		if (parse_n_export(ctrl, *flag))
			status = 1;
		if (errno)
		{
			ft_dprintf(STDERR_FILENO, "minishell: export: %s\n", *flag);
			return (1);
		}
		flag++;
	}
	return (status);
}
