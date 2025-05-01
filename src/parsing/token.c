/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:36:42 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 12:32:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "environ.h"
#include "minishell.h"
#include "parsing.h"

static bool isvalidchar(char quotes, char c)
{
	if (!quotes)
		return (!ft_strchr("<>|", c) && !ft_isspace(c));
	else
		return (true);
}

static size_t	token_len(t_ctrl *ctrl, char *str, bool isexpand)
{
	size_t	total_len;
	char	quotes[2];
	size_t	i;

	total_len = 1;
	ft_bzero(&quotes, 2);
	i = 0;
	while (str[i] && isvalidchar(quotes[0], str[i]))
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (isexpand && str[i] == '$')
			total_len += ft_strlen(get_env(env_to_array(ctrl->environ), str + i + 1, &i));
		if ((!quotes[0] && ft_isspace(str[i]))
			|| (quotes[1] == '\'' && str[i] == '\'') || (quotes[1] == '"' && str[i] == '"'))
			total_len--;
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

static size_t	construct_token(t_ctrl *ctrl, char *str, bool isexpand, char *token)
{
	char	quotes[2];
	char	*expand;
	size_t	i;
	size_t	j;

	ft_bzero(&quotes, 2);
	i = 0;
	j = 0;
	while (str[i] && isvalidchar(quotes[1], str[i]))
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (VERBOSE)
			ft_printf("Char %c, i: %u, j: %u, quotes[0]: %c\n", str[i], i, j, quotes[0]);
		if (quotes[0] != '\'' && isexpand && str[i] == '$')
		{
			expand = get_env(env_to_array(ctrl->environ), str + i + 1, &i);
			ft_strlcpy(str + j, expand, ft_strlen(expand));
			j += ft_strlen(expand);
		}
		else if (quotes[0] != str[i])
			token[j++] = str[i];
		i++;
	}
	token[j] = '\0';
	return (i);
}

char *sub_token(t_ctrl *ctrl, char *str, size_t *len, bool isexpand)
{
	size_t	total_len;
	char	*token;

	total_len = token_len(ctrl, str, isexpand);
	if (errno)
	{
		*len = 0;
		return (NULL);
	}
	token = malloc(total_len);
	if (!token)
		return (NULL);
	*len += construct_token(ctrl, str, isexpand, token);
	return (token);
}
