/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:16:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 18:48:42 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "commands.h"
#include "ft_vector.h"
#include "libft.h"
#include "minishell.h"
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*get_expanded(t_ctrl *ctrl, char *str, char quotes[2])
{
	t_vector	outstr;
	size_t		i;
	char		*expand;

	outstr = vec_new(64, sizeof(char));
	if (!outstr.data)
		return (NULL);
	i = -1;
	while (!errno && str[++i])
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (quotes[0] == '"' && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			if (get_expand(ctrl->environ, str + i, &i, &expand))
				outstr = vec_add(outstr, vec_from_string(expand));
		}
		else if (quotes[0] != str[i])
		{
			i = skip_backslash(quotes, i, str);
			vec_append(&outstr, str + i);
		}
	}
	if (!errno)
		vec_append_int(&outstr, 0);
	return ((char *)outstr.data);
}

int	get_expand(t_env *lst, char *key, size_t *out_len, char **value)
{
	char	oldone;
	size_t	len;

	len = 1;
	while (key[len] && (ft_isalnum(key[len]) || key[len] == '_'))
		len++;
	if (len == 1)
	{
		*value = NULL;
		return (0);
	}
	*out_len += len - 1;
	oldone = key[len];
	key[len] = '\0';
	*value = get_env(lst, key + 1);
	key[len] = oldone;
	return ((*value != NULL));
}

t_vector	secure_expand_operators(char *str)
{
	t_vector	expand;
	size_t		i;

	expand = vec_from_string(str);
	i = 0;
	while (!errno && i < (size_t)expand.actual_size)
	{
		if (ft_strchr("<>|\\", ((char *)expand.data)[i]))
			vec_insert_int(&expand, '\\', i++);
		i++;
	}
	return (expand);
}

char	*chunk_expand(t_ctrl *ctrl, char *str)
{
	char		quotes[2];
	char		*expand;
	t_vector	outstr;
	size_t		i;

	outstr = vec_new(64, sizeof(char));
	if (!outstr.data)
		return (NULL);
	ft_bzero(quotes, 2);
	i = 0;
	while (!errno && str[i])
	{
		check_quotes(str[i], &quotes[0], &quotes[1]);
		if (!quotes[0] && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			if (get_expand(ctrl->environ, str + i, &i, &expand))
				outstr = vec_add(outstr, secure_expand_operators(expand));
		}
		else
			vec_append(&outstr, str + i);
		i++;
	}
	if (!errno)
		vec_append_int(&outstr, 0);
	return ((char *)outstr.data);
}

int	array_expand_all(t_ctrl *ctrl, t_vector array)
{
	char		**chunks;
	char		*expanded;
	ssize_t		i;

	chunks = (char **)array.data;
	i = 0;
	while (!errno && i < array.actual_size)
	{
		if (i == 0 || ft_strcmp(chunks[i - 1], "<<"))
		{
			expanded = chunk_expand(ctrl, chunks[i]);
			free(chunks[i]);
			chunks[i] = expanded;
		}
		i++;
	}
	return (0);
}
