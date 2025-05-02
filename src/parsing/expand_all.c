/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:15:39 by dderny            #+#    #+#             */
/*   Updated: 2025/05/02 15:55:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "minishell.h"
#include "parsing.h"

static size_t	construct_len(t_ctrl *ctrl, char *str)
{
	size_t	total_len;
	char	*expand;
	char	quotes[2];
	size_t	i;

	total_len = 1;
	ft_bzero(&quotes, 2);
	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (!quotes[0] && str[i] == '$')
		{
			if (parse_expand(ctrl->environ, str + i, &i, &expand))
				total_len += ft_strlen(expand) - 1;
		}
		i++;
	}
	total_len += i;
	if (quotes[1] == '\'' || quotes[1] == '"')
	{
		errno = EINVAL;
		ft_dprintf(STDERR_FILENO, "Syntax error: unmatched %c\n", quotes[0]);
	}
	return (total_len);
}

static void	construct_string(t_ctrl *ctrl, char *str, char *strout)
{
	char	quotes[2];
	char	*expand;
	size_t	i;
	size_t	j;

	ft_bzero(&quotes, 2);
	i = 0;
	j = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (!quotes[0] && str[i] == '$')
		{
			if (parse_expand(ctrl->environ, str + i, &i, &expand))
			{
				ft_memcpy(strout + j, expand, ft_strlen(expand));
				j += ft_strlen(expand);
			}
		}
		else
			strout[j++] = str[i];
		i++;
	}
	strout[j] = '\0';
}

char *expand_all(t_ctrl *ctrl, char *str)
{
	size_t	total_len;
	char	*token;

	total_len = construct_len(ctrl, str);
	if (errno)
		return (NULL);
	token = ft_calloc(total_len, sizeof(char));
	if (!token)
		return (NULL);
	construct_string(ctrl, str, token);
	return (token);
}
