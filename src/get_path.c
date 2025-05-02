/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:41:59 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 16:16:47 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

void	*ft_free_path(void **array, char *s1, char *s2)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	free(s1);
	free(s2);
	return (NULL);
}


char	*concat_path(char *s1, char c, char *s2)
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
		ret[ct_ret] = s2[ct];
		++ct;
		++ct_ret;
	}
	ret[ct_ret] = c;
	ct = 0;
	while (s1[ct] != '\0')
	{
		ret[++ct_ret] = s2[ct];
		++ct;
	}
	ret[++ct_ret] = '\0';
	return (ret);
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

char	*pars_path(char *path, char *to_find)
{
	size_t	ct;
	char	**tab;
	char	*temp;

	ct = 0;
	if (path == NULL)
		return (NULL);
	tab = ft_split(path, ":");
	if (tab == NULL)
		return (NULL);
	while (tab[ct] != NULL)
	{
		temp = concat_path(tab[ct], '/', to_find);
		if (temp == NULL)
			return (ft_freearray(tab, path, to_find));
		if (check_stat(temp) == true)
		{
			ft_freearray(tab, path, to_find);
			return (temp);
		}
		free(temp);
		++ct;
	}
	return (ft_freearray(tab, path, to_find));
}

bool	check_stat(char	*path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	if (S_ISDIR(st.st_mode))
		return (false);
	return (true);
}
