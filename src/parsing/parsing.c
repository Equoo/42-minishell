/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:28:00 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 10:35:41 by dderny           ###   ########.fr       */
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

int	check_quotes(char c, char *surrounder, char *next_surrounder)
{
	if (!*next_surrounder)
		*surrounder = 0;
	if (c == '\'' || c == '"')
	{
		if (*surrounder == 0)
		{
			*surrounder = c;
			*next_surrounder = c;
		}
		else if (*surrounder == c)
			*next_surrounder = 0;
		return (1);
	}
	return (0);
}

static int	get_expand(t_env *lst, char *key, size_t *out_len, char **value)
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

char *get_expanded(t_ctrl *ctrl, char *str)
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
		if (quotes[0] == '"' && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			if (get_expand(ctrl->environ, str + i, &i, &expand))
				outstr = vec_add(outstr, vec_from_string(expand));
		}
		else if (quotes[0] != str[i] && !(!quotes[0] && str[i] == '\\' && ft_strchr("<>|", str[i + 1])))
		{
			__builtin_printf("%zu] = %c %c\n", i, str[i], str[i + 1]);
			vec_append(&outstr, str + i);
		}
		i++;
	}
	if (!errno)
		vec_append_int(&outstr, 0);
	return ((char *)outstr.data);
}

t_vector	split_by_spaces_and_operators(char *strcmd, bool operators)
{
	char		quotes[2];
	t_vector	array;
	size_t		i;
	size_t		len;

	array = vec_new(8, sizeof(char *));
	if (!array.data)
		return (array);
	ft_bzero(quotes, 2);
	i = -1;
	len = 0;
	while (!errno && strcmd[++i])
	{
		check_quotes(strcmd[i], &quotes[0], &quotes[1]);
		if (len && (!*quotes && ft_isspace(strcmd[i])))
		{
			vec_append_ulong(&array, (uintptr_t)ft_substr(strcmd, i - len, len));
			len = 0;
		}
		else if (!*quotes && operators && ft_strchr("<>|", strcmd[i]))
		{
			if (len)
				vec_append_ulong(&array, (uintptr_t)ft_substr(strcmd, i - len, len));
			len = 0;
			while (strcmd[i] && ft_strchr("<>|", strcmd[i]) && ++len)
				i++;
			if (!errno)
				vec_append_ulong(&array, (uintptr_t)ft_substr(strcmd, i-- - len, len));
			len = 0;
		}
		else if (*quotes || !ft_isspace(strcmd[i]))
			len++;
	}
	if (!errno && len)
		vec_append_ulong(&array, (uintptr_t)ft_substr(strcmd, i - len, len));
	return (array);
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

char *chunk_expand(t_ctrl *ctrl, char *str)
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

int	array_split_chunks(t_vector *array)
{
	char		**chunks;
	t_vector	subchunks;
	ssize_t		i;

	i = 0;
	while (!errno && i < array->actual_size)
	{
		chunks = (char **)array->data;
		subchunks = split_by_spaces_and_operators(chunks[i], false);
		if (subchunks.actual_size == 1)
			free(((char **)subchunks.data)[0]);
		if (subchunks.actual_size > 1)
		{
			free(chunks[i]);
			vec_remove(array, i);
			*array = vec_insert(*array, subchunks, i);
		}
		else
			free(subchunks.data);
		if (subchunks.actual_size)
			i += subchunks.actual_size;
		else
			i++;
	}
	return (0);
}

static int	parse_per_types(t_ctrl *ctrl, t_vector array,
	t_command *cmd, t_vector *args)
{
	char		**chunks;
	char		*expanded;
	ssize_t		i;

	i = 0;
	chunks = (char **)array.data;
	while (!errno && i < array.actual_size)
	{
		__builtin_printf("chunks[%zu] = %s, on %zu\n", i, chunks[i], array.actual_size);
		if (ft_strchr("<>", chunks[i][0]) && ++i)
			parse_redirection(ctrl, chunks[i - 1], chunks[i], cmd);
		else if (chunks[i][0] == '|')
			parse_pipe(ctrl, chunks[i], cmd, args);
		else
		{
			expanded = get_expanded(ctrl, chunks[i]);
			if (!expanded)
				return (1);
			vec_append(args, &expanded);
		}
		free(chunks[i]);
		i++;
	}
	free(chunks);
	return (0);
}

int	parse_command(t_ctrl *ctrl, char *strcmd)
{
	t_vector	array;
	t_command		cmd;
	t_vector		args;

	array = split_by_spaces_and_operators(strcmd, true);
	if (!errno)
		array_expand_all(ctrl, array);
	if (!errno)
		array_split_chunks(&array);
	if (!errno)
		args = vec_new(8, sizeof(char *));

	cmd = (t_command){.in.fd = -1, .out.fd = -1, .args = NULL};
	if (!args.data || parse_per_types(ctrl, array, &cmd, &args))
		return (0);

	if (args.actual_size > 0)
	{
		cmd.args = (char **)args.data;
		if (vec_append_ulong(&args, (uintptr_t)NULL) || commands_append(&ctrl->commands, cmd))
		{
			ft_freearray((void **)cmd.args);
			return (0);
		}
	}
	else if (cmd.in.type == IO_PIPE || cmd.out.type == IO_PIPE)
	{
		token_error(NULL, '|');
		ft_freearray((void **)cmd.args);
		return (0);
	}
	return (1);
}

