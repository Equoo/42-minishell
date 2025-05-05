/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:10:42 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 06:43:47 by dderny           ###   ########.fr       */
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
		if (!ft_strncmp(tmp->key, to_find, ft_strlen(to_find) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
