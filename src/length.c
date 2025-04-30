/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:01:24 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 05:17:14 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	ct;

	ct = 0;
	if (str == NULL)
		return (0);
	while (str[ct] != '\0')
		++ct;
	return (ct);
}

size_t	ft_tablen(char **table)
{
	size_t	ct;

	ct = 0;
	while (table[ct] != NULL)
		++ct;
	return (ct);
}

size_t	ft_strlen_select(char *str, char c)
{
	size_t	ct;

	ct = 0;
	while (str[ct] != '\0' && str[ct] != c)
		++ct;
	return (ct);
}

size_t	ft_lstlen(t_env *lst)
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