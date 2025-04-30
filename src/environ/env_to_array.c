/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:08:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 00:22:03 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <libft.h>
#include <stdlib.h>

static char	*concat_env(char *key, char *val)
{
	char	*ret;
	size_t	ct;
	size_t	ct_ret;

	ct = 0;
	ct_ret = 0;
	ret = malloc(sizeof(char) * ft_strlen(key) + ft_strlen(val) + 2);
	if (ret == NULL)
		return (NULL);
	while (key[ct] != '\0')
	{
		ret[ct_ret] = key[ct];
		++ct;
		++ct_ret;
	}
	ct = 0;
	if (val != NULL)
	{
		ret[ct_ret] = '=';
		while (val[ct] != '\0')
		{
			ret[++ct_ret] = val[ct];
			++ct;
		}
		ret[++ct_ret] = '\0';
	}
	else
		ret[ct_ret] = '\0';
	return (ret);
}

char	**env_to_array(t_env *lst)
{
	t_env	*cpy;
	size_t	ct;
	char	**ret;

	cpy = lst;
	ct = 0;
	ret = malloc(sizeof(char *) * (ft_envslen(cpy) + 1));
	if (ret == NULL)
		return (NULL);
	while (cpy != NULL)
	{
		ret[ct] = concat_env(cpy->key, cpy->value);
		if (ret[ct] == NULL)
		{
			ft_freearray((void **)ret);
			return (NULL);
		}
		cpy = cpy->next;
		++ct;
	}
	ret[ct] = NULL;
	return (ret);
}
