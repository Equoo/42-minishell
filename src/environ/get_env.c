/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:10:42 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 16:54:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <libft.h>

char	*get_env(t_env *lst, char *to_find)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, to_find))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
