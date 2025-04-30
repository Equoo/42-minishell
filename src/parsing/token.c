/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:36:42 by dderny            #+#    #+#             */
/*   Updated: 2025/05/01 00:59:03 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "environ.h"
#include "parsing.h"

static bool isvalidchar(char surrounder, char c)
{
	if (!surrounder)
		return (!ft_strchr("<>|", c) && !ft_isspace(c));
	else
		return (true);
}

char *sub_token(t_ctrl *ctrl, char *str, size_t *len, bool isexpand)
{
	char	next_surrounder;
	char	surrounder;
	size_t	total_len;
	char	*expand;
	char	*token;
	size_t	i;
	size_t	j;

	total_len = 1;
	next_surrounder = 0;
	surrounder = 0;
	i = 0;
	while (str[i] && isvalidchar(surrounder, str[i]))
	{
		check_quotes(str[i], &surrounder, &next_surrounder);
		if (isexpand && str[i] == '$')
			total_len += ft_strlen(get_env(env_to_array(ctrl->environ), str + i + 1, &i));
		if ((!surrounder && ft_isspace(str[i])) || (next_surrounder == '\'' && str[i] == '\'') || (next_surrounder == '"' && str[i] == '"'))
			total_len--;
		i++;
	}
	total_len += i;
	printf("Total %zu\n", total_len);
	token = malloc(total_len);
	if (!token)
		return (NULL);
	next_surrounder = 0;
	surrounder = 0;
	i = 0;
	j = 0;
	while (str[i] && isvalidchar(next_surrounder, str[i]))
	{
		check_quotes(str[i], &surrounder, &next_surrounder);
		printf("Char %c, i: %zu, j: %zu, surrounder: %c\n", str[i], i, j, surrounder);
		if (surrounder != '\'' && isexpand && str[i] == '$')
		{
			expand = get_env(env_to_array(ctrl->environ), str + i + 1, &i);
			ft_strlcpy(str + j, expand, ft_strlen(expand));
			j += ft_strlen(expand);
		}
		else if (surrounder != str[i])
			token[j++] = str[i];
		i++;
	}
	*len += i;
	token[j] = '\0';
	if (next_surrounder == '\'' || next_surrounder == '"')
	{
		errno = EINVAL;
		ft_dprintf(STDERR_FILENO, "Syntax error: unmatched %c\n", surrounder);
		free(token);
		return (NULL);
	}
	return (token);
}