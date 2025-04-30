/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:04:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 23:33:43 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *lst)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (cpy->key != NULL && cpy->value != NULL)
		{
			ft_putstr(cpy->key);
			ft_putchar('=');
			ft_putstr(cpy->value);
			ft_putchar('\n');
		}
		cpy = cpy->next;
	}
}
