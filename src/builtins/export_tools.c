/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:24:15 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 00:36:48 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "environ.h"
#include "builtin.h"

bool	secure_export(char *key)
{
	size_t	ct;

	ct = 0;
	if (!(key[0] >= 65 && key[0] <= 90)
		&& !(key[0] >= 97 && key[0] <= 122) && !(key[0] == '_'))
	{
		ft_dprintf(STDERR_FILENO, "Bad identifier\n");
		return (false);
	}
	while (key[ct] != '\0')
	{
		if (!(key[ct] >= 48 && key[ct] <= 57)
			&& !(key[ct] >= 65 && key[ct] <= 90)
			&& !(key[ct] >= 97 && key[ct] <= 122) && !(key[ct] == '_'))
		{
			ft_dprintf(STDERR_FILENO, "Bad identifier\n");
			return (false);
		}
		++ct;
	}
	return (true);
}

bool	replace_node(t_env *node, char *new_value)
{
	free(node->value);
	node->value = new_value;
	return (true);
}
