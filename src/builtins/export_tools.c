/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:24:15 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 13:13:46 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "environ.h"
#include "builtin.h"
#include <stdlib.h>
#include "libft.h"

void	sort_table(t_env *lst, char **table)
{
	size_t	ct;
	char	*save;

	ct = 0;
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
}

bool	secure_export(char *key)
{
	size_t	ct;

	ct = 0;
	if (!(key[0] >= 65 && key[0] <= 90)
		&& !(key[0] >= 97 && key[0] <= 122) && !(key[0] == '_'))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", key);
		return (false);
	}
	while (key[ct] != '\0')
	{
		if (!(key[ct] >= 48 && key[ct] <= 57)
			&& !(key[ct] >= 65 && key[ct] <= 90)
			&& !(key[ct] >= 97 && key[ct] <= 122) && !(key[ct] == '_'))
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", key);
			return (false);
		}
		++ct;
	}
	return (true);
}

bool	replace_node(t_env *node, char *new_key, char *new_value)
{
	free(node->value);
	free(node->key);
	node->value = new_value;
	node->key = new_key;
	return (true);
}

void	print_export(char **table, int fd)
{
	size_t	ct;

	ct = 0;
	while (table[ct] != NULL)
	{
		if (table[ct][0] != '_')
		{
			write(fd, "declare -x ", 12);
			print_var_export(table[ct], fd);
			write(fd, "\n", 1);
		}
		++ct;
	}
}

void	print_var_export(char *str, int fd)
{
	size_t	ct;

	ct = 0;
	while (str[ct] != '\0' && str[ct] != '=')
	{
		write(fd, &str[ct], 1);
		++ct;
	}
	if (str[ct] == '=' && str[ct + 1] == '\0')
		ft_dprintf(fd, "%c%c", 34, 34);
	else if (str[ct] != '\0' && str[ct + 1] != '\0')
	{
		write(fd, &str[ct], 1);
		ft_dprintf(fd, "%c", 34);
		while (str[++ct] != '\0')
			write(fd, &str[ct], 1);
		ft_dprintf(fd, "%c", 34);
	}
}
