/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:41:59 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 18:17:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

static void	*ft_free_path(char **array, char *s2)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	if (s2 != NULL)
		free(s2);
	return (NULL);
}

static char	*concat_path(char *s1, char c, char *s2)
{
	size_t	ct;
	size_t	ct_ret;
	char	*ret;

	ct = 0;
	ct_ret = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (ret == NULL)
		return (NULL);
	while (s1[ct] != '\0')
	{
		ret[ct_ret] = s1[ct];
		++ct;
		++ct_ret;
	}
	ret[ct_ret] = c;
	ct = 0;
	while (s2[ct] != '\0')
	{
		ret[++ct_ret] = s2[ct];
		++ct;
	}
	ret[++ct_ret] = '\0';
	return (ret);
}

static bool	check_stat(char	*path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	if (errno == ENOENT)
		errno = 0;
	if (S_ISDIR(st.st_mode))
		return (false);
	return (true);
}


static char	*pars_path(char *path, char *to_find)
{
	size_t	ct;
	char	**tab;
	char	*temp;

	ct = 0;
	if (path == NULL)
		return (NULL);
	tab = ft_split(path, ':');
	if (tab == NULL)
		return (NULL);
	while (tab[ct] != NULL)
	{
		temp = concat_path(tab[ct], '/', to_find);
		if (temp == NULL)
			return (ft_free_path(tab, NULL));
		if (check_stat(temp) == true)
		{
			ft_free_path(tab, to_find);
			return (temp);
		}
		free(temp);
		++ct;
	}
	return (ft_free_path(tab, NULL));
}

char	*get_path(t_env *lst, char *command)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (ft_strcmp(cpy->key, "PATH") == 0)
			return (pars_path(cpy->value, command));
		cpy = cpy->next;
	}
	return (NULL);
}

