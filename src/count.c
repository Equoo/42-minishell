/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:09:35 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 08:22:12 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_pipe(char *str, char c)
{
	size_t	ct;
	size_t	ret;
	bool	doubl;
	bool	simpl;

	ret = 0;
	simpl = false;
	doubl = false;
	ct = 0;
	while (str[ct] != '\0')
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
		if (str[ct] == c && doubl == false && simpl == false)
			++ret;
		++ct;
	}
}