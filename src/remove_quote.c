/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:17:21 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 08:21:13 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(char *str)
{
	char	*ret;
	size_t	ct;
	size_t	ct_alloc;

	ct = 0;
	ct_alloc = 0;
	while (str[ct] != '\0')
	{
		if (str[ct] != 39 && str[ct] != '"')
			++ct_alloc;
		++ct;
	}
	ret = malloc(sizeof(char) * ct_alloc + 1);
	if (ret == NULL)
		return (NULL);
	ct_alloc = 0;
	ct = 0;
	while (str[ct] != '\0')
	{
		if (str[ct] != 39 && str[ct] != '"')
		{
			ret[ct_alloc] = str[ct];
			++ct_alloc;
		}
	}
	ret[ct_alloc] = '\0';
	return (ret);
}