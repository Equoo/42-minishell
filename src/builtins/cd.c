/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 11:13:14 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

bool	ft_cd(t_ctrl *ctrl, char *path)
{
	//char	*buffer;

	(void)ctrl;
	if (chdir(path) == -1)
		return (false);
	else
	{
		//ctrl->pwd = getcwd(buffer, 4096);
		return (true);
	}
	return (false);
}
