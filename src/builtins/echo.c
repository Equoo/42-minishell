/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:32:08 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 22:20:39 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdbool.h>
#include <unistd.h>
#include "minishell.h"


int	ft_echo(t_ctrl *ctrl, char **flag)
{
	bool	new_line;
	size_t	ct;

	(void) ctrl;
	ct = 1;
	new_line = false;
	if (ft_strcmp(flag[1], "-n") == 0)
	{
		++ct;
		new_line = true;
	}
	if (ft_strcmp(flag[1], "$?") == 0)
	{
//		write(1, ctrl->exit, ft_strlen(flag[ct]));
		ctrl->exit = 0;
	}
	while (flag[ct] != NULL)
	{
		write(1, flag[ct], ft_strlen(flag[ct]));
		if (flag[ct + 1] != NULL)
			write(1, " ", 1);
		++ct;
	}
	if (new_line == true)
		write(1, "\n", 1);
	return (0);
}
