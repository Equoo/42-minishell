/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:26 by dderny            #+#    #+#             */
/*   Updated: 2025/04/30 17:39:49 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

char	*get_env(char **env, char *key, size_t *out_len)
{
	char	oldone;
	size_t	len;
	size_t	i;

	len = 0;
	while (key[len] && (ft_isalpha(key[len]) || key[len] == '_'))
		len++;
	if (!len)
		return ("");
	*out_len += len;
	key[len] = '\0';
	oldone = key[len];
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], key))
			return (env[i + 1]);
		i++;
		if (env[i])
			i++;
		else
			break ;
	}
	key[len] = oldone;
	return (NULL);
}
