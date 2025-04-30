/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:00:22 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 07:13:46 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	size_t	ct;
	char	*ret;

	ct = 0;
	if (str == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (ret == NULL)
		return (NULL);
	while (str[ct] != '\0')
	{
		ret[ct] = str[ct];
		++ct;
	}
	ret[ct] = '\0';
	return (ret);
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

char	*ft_strdup_quote(char *str, char c)
{
	size_t	ct;
	char	*ret;
	bool	simpl;
	bool	doubl;

	doubl = false;
	simpl = false;
	ct = 0;
	while (str[ct] != '\0' && (str[ct] != c && simpl == false && doubl == false))
	{
		if (str[ct] == 39)
		{
			if (simpl == false)
				simpl = true;
			else
				simpl = false;
		}
		if (str[ct] == '"')
		{
			if (doubl == false)
				doubl = true;
			else
				doubl = false;
		}
		ct++;
	}
	ret = malloc(sizeof(char) * ct + 1);
	if (ret == NULL)
		return (NULL);
	ct = 0;
	doubl = false;
	simpl = false;
	while (str[ct] != '\0' && (str[ct] != c && simpl == false && doubl == false))
	{
		if (str[ct] == 39)
		{
			if (simpl == false)
				simpl = true;
			else
				simpl = false;
		}
		if (str[ct] == '"')
		{
			if (doubl == false)
				doubl = true;
			else
				doubl = false;
		}
		ret[ct] = str[ct];
		ct++;
	}
	ret[ct] = '\0';
	return (ret);
}
