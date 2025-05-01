/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:26 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 17:09:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stddef.h>
#include <libft.h>

int parse_expand(t_env *lst, char *key, size_t *out_len, char **value)
{
	char	oldone;
	size_t	len;

	len = 1;
	while (key[len] && (ft_isalpha(key[len]) || key[len] == '_'))
		len++;
	if (len == 1)
	{
		*value = NULL;
		return (0);
	}
	*out_len += len - 1;
	oldone = key[len];
	key[len] = '\0';
	*value = get_env(lst, key + 1);
	key[len] = oldone;
	return ((*value != NULL));
}
