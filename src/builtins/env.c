/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:04:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 00:45:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include "environ.h"

void	ft_env(t_env *lst)
{
	t_env	*cpy;

	cpy = lst;
	while (cpy != NULL)
	{
		if (cpy->key != NULL && cpy->value != NULL)
		{
			ft_putstr_fd(cpy->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(cpy->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		cpy = cpy->next;
	}
}
