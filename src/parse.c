/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:32:06 by dderny            #+#    #+#             */
/*   Updated: 2025/04/30 04:52:50 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "commands.h"
//#include "ft_vector.h"
#include <errno.h>
//#include <libft.h>
#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


typedef struct s_parse
{
	char	surrounder; // none or ' or "
	char	**pipes;

}	t_parse;

static char	**split(const char *s, char c)
{
	t_vector	array;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	array = vec_new(8, sizeof(char *));
	if (!array.data)
		return (NULL);
	i = 0;
	j = 0;
	char	*str;
	while (s[j])
	{
		j = i;
		while (s[j] && (unsigned char)s[j] != (unsigned char)c)
			j++;
		str = ft_substr(s, i, (size_t)(j - i));
		if (!str || vec_append(&array, str))
			return (NULL);
		i = j + 1;
	}
	return ((char **)array.data);
}


int	main(int argc, char **argv, char **env)
{
	(void)env;
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <command> [args]\n", argv[0]);
		return (1);
	}

	char 	*cmd = argv[1];
	int 	i = 0;
	char	last = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' && (last == '|' || !cmd[i + 1]))
		{
			fprintf(stderr, "Error: syntax error near unexpected token |\n");
			return (1);
		}
		last = cmd[i];
		i++;
	}
	char **pipes = ft_split(cmd, '|');
	if (!pipes)
	{
		fprintf(stderr, "Error: failed to split command\n");
		return (1);
	}
	i = 0;
	while (pipes[i])
	{

		printf("Pipe %d: %s\n", i, pipes[i]);
		i++;
	}

	return (0);
}
