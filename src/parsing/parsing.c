/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:28:00 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 14:04:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "commands.h"
#include "ft_printf.h"
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
#include <unistd.h>

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
	}
	return (1);
}

static t_vector	split_spaces_ops(char *strcmd,
		bool operators, size_t i, size_t len)
{
	char		qt[2];
	t_vector	array;

	array = vec_new(8, sizeof(char *));
	if (!array.data)
		return (array);
	ft_bzero(qt, 2);
	while (!errno && strcmd[++i] && check_quotes(strcmd[i], &qt[0], &qt[1]))
	{
		if (len && (!*qt && ft_isspace(strcmd[i])))
			len = vec_secure(&array, ft_substr(strcmd, i - len, len));
		else if (!*qt && operators && ft_strchr("<>|", strcmd[i]))
		{
			if (len)
				len = vec_secure(&array, ft_substr(strcmd, i - len, len));
			while (strcmd[i] && ft_strchr("<>|", strcmd[i]) && ++len)
				i++;
			len = vec_secure(&array, ft_substr(strcmd, i-- - len, len));
		}
		else if (*qt || !ft_isspace(strcmd[i]))
			len++;
	}
	if (len)
		vec_secure(&array, ft_substr(strcmd, i - len, len));
	return (array);
}

int	array_split_chunks(t_vector *array)
{
	t_vector	subchunks;
	ssize_t		i;

	i = 0;
	while (!errno && i < array->actual_size)
	{
		if (i > 0 && ft_strchr("<>", ((char **)array->data)[i - 1][0]) && ++i)
			continue ;
		subchunks = split_spaces_ops(((char **)array->data)[i], false, -1, 0);
		if (subchunks.actual_size == 1)
			free(((char **)subchunks.data)[0]);
		if (subchunks.actual_size > 1)
		{
			free(((char **)array->data)[i]);
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
	char		quotes[2];
	ssize_t		i;

	i = -1;
	ft_bzero(quotes, 2);
	chunks = (char **)array.data;
	while (!errno && ++i < array.actual_size)
	{
		if (i + 1 < array.actual_size && ft_strchr("<>", chunks[i][0]) && ++i)
			parse_redirection(ctrl, chunks[i - 1], chunks[i], cmd);
		else if (chunks[i][0] == '|')
			parse_pipe(ctrl, chunks[i], cmd, args);
		else
		{
			expanded = get_expanded(ctrl, chunks[i], quotes);
			if (!expanded)
				return (1);
			vec_append(args, &expanded);
		}
		free(chunks[i]);
	}
	free(chunks);
	return (0);
}

int	parse_command(t_ctrl *ctrl, char *strcmd)
{
	t_vector		array;
	t_command		cmd;
	t_vector		args;

	array = split_spaces_ops(strcmd, true, -1, 0);
	if (!errno)
		array_expand_all(ctrl, array);
	if (!errno)
		array_split_chunks(&array);
	if (!errno)
		args = vec_new(8, sizeof(char *));
	cmd = (t_command){.in.fd = -1, .out.fd = -1, .args = NULL};
	if (!args.data || parse_per_types(ctrl, array, &cmd, &args))
		return (0);
	return (last_command(cmd, ctrl, args));
}
