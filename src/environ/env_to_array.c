/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:08:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 14:42:56 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <libft.h>
#include <stdlib.h>

static char	*pars_concat_env(char *ret, char *key, char *val)
{
	size_t	ct;
	size_t	ct_ret;

	ct = -1;
	ct_ret = -1;
	while (key[++ct] != '\0')
		ret[++ct_ret] = key[ct];
	ct = 0;
	if (val != NULL)
	{
		ret[++ct_ret] = '=';
		while (val[ct] != '\0')
		{
			ret[++ct_ret] = val[ct];
			++ct;
		}
		ret[++ct_ret] = '\0';
	}
	else
		ret[++ct_ret] = '\0';
	return (ret);
}

static char	*concat_env(char *key, char *val)
{
	char	*ret;

	if (val == NULL)
		ret = malloc(sizeof(char) * ft_strlen(key) + 2);
	else
		ret = malloc(sizeof(char) * ft_strlen(key) + ft_strlen(val) + 2);
	if (ret == NULL)
		return (NULL);
	return (pars_concat_env(ret, key, val));
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
	if (cpy == NULL)
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
