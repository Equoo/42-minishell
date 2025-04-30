/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:13:16 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 05:22:57 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_env(char *key, char *val)
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