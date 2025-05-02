/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:54:54 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:15:52 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H
# include <stdbool.h>
# include <stddef.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_init(char **env);

bool	add_env(t_env **lst, char *env, size_t ct);
bool	set_env_val(t_env *node, char *env);
void	free_env(t_env *node);
void	free_envs(t_env *lst);

size_t	ft_envslen(t_env *lst);

char	**env_to_array(t_env *lst);

char	*ft_strdup_select(char *str, char c);

char	*get_env(t_env *lst, char *to_find);
size_t	ft_strlen_select(char *str, char c);
bool	add_node_env(t_env *lst, char *key, char *val);

#endif
