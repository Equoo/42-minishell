/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:10:42 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 16:22:46 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(t_env *lst, char *to_find)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (ft_strcmp(lst->key, to_find) == 0)
			return (lst->value);
		cpy = cpy->next;
	}
	return (NULL);
}


