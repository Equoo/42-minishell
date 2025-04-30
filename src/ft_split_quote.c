/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:01:49 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 08:22:48 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_split(char **tab)
{
	size_t	ct;

	ct = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[ct])
	{
		free(tab[ct]);
		ct++;
	}
	free(tab);
	return (NULL);
}

char	**ft_quote_split(char *str, char c)
{
	char	**ret;
	size_t	ct;
	size_t	ct_tab;
	bool	doubl;
	bool	simpl;

	ret = malloc(sizeof(char *) * (count_pipe(str, c) + 1));
	if (ret == NULL)
		return (NULL);
	ct = 0;
	ct_tab = 0;
	while (str[ct] != '\0')
	{
		while (str[ct] == c)
			ct++;
		if (str[ct] != '\0' && simpl == false && doubl == false)
		{
			ret[ct_tab] = ft_strdup_quote(&str[ct], c);
			if (ret[ct_tab] == NULL)
				return (ft_free_all(ret));
			ct_tab++;
		}
		while (str[ct] != c && str[ct] != '\0')
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
	}
	ret[ct_tab] = NULL;
	return (ret);
}
