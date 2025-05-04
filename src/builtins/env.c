/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:04:12 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 13:02:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <unistd.h>
#include "environ.h"
#include "ft_printf.h"
#include "minishell.h"

int	ft_env(t_ctrl *ctrl, char **flag, int fd)
{
	t_env	*cpy;

	if (flag[1] != NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: env: %s: doesn't take arguments\n", flag[1]);
		return (1);
	}
	cpy = ctrl->environ;
	while (cpy != NULL)
	{
		if (cpy->key != NULL && cpy->value != NULL)
		{
			ft_putstr_fd(cpy->key, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd(cpy->value, fd);
			ft_putchar_fd('\n', fd);
		}
		cpy = cpy->next;
	}
	return (0);
}
