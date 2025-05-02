/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:04:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 20:20:26 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include "environ.h"
# include "minishell.h"


int	ft_env(t_ctrl *ctrl, char **flag)
{
	t_env	*cpy;

	if (flag[1] != NULL)
		return (-1);
	cpy = ctrl->environ;
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
	return (0);
}
