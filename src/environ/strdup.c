/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:00:22 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 05:49:08 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdbool.h>
#include <stdlib.h>

bool	swap_bool(bool quote)
{
	if (quote == false)
		return (true);
	return (false);
}

char	*ft_strdup_select(char *str, char c)
{
	size_t	ct;
	char	*ret;

	ct = 0;
	ret = malloc(sizeof(char) * ft_strlen_select(str, c) + 1);
	if (ret == NULL)
		return (NULL);
	while (str[ct] != '\0' && str[ct] != c)
	{
		ret[ct] = str[ct];
		++ct;
	}
	ret[ct] = '\0';
	return (ret);
}

size_t	alloc_len_quote(char *str, char c)
{
	size_t	ret;
	bool	simpl;
	bool	doubl;

	doubl = false;
	simpl = false;
	ret = 0;
	while (str[ret] != '\0'
		&& (str[ret] != c && simpl == false && doubl == false))
	{
		if (str[ret] == 39)
			simpl = swap_bool(simpl);
		if (str[ret] == '"')
			doubl = swap_bool(doubl);
		ret++;
	}
	return (ret);
}

char	*ft_strdup_quote(char *str, char c)
{
	size_t	ct;
	char	*ret;
	bool	simpl;
	bool	doubl;

	doubl = false;
	simpl = false;
	ct = 0;
	ret = malloc(sizeof(char) * alloc_len_quote(str, c) + 1);
	if (ret == NULL)
		return (NULL);
	while (str[ct] != '\0'
		&& (str[ct] != c && simpl == false && doubl == false))
	{
		if (str[ct] == 39)
			simpl = swap_bool(simpl);
		if (str[ct] == '"')
			doubl = swap_bool(doubl);
		ret[ct] = str[ct];
		ct++;
	}
	ret[ct] = '\0';
	return (ret);
}
