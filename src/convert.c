/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:08:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 01:21:13 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_table(char **table)
{
	size_t	ct;

	ct = 0;
	while (table[ct] != NULL)
	{
		free(table[ct]);
		++ct;
	}
	free(table);
	return (NULL);
}

char	**lst_to_tab(t_env *lst)
{
	t_env	*cpy;
	size_t	ct;
	char	**ret;

	cpy = lst;
	ct = 0;
	ret = malloc(sizeof(char *) * (ft_lstlen(cpy) + 1));
	if (ret == NULL)
		return (NULL);
	while (cpy != NULL)
	{
		ret[ct] = concat_env(cpy->key, cpy->value);
		if (ret[ct] == NULL)
			return (free_table(ret));
		cpy = cpy->next;
		++ct;
	}
	ret[ct] = NULL;
	return (ret);
}
