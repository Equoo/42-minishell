/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:01:41 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 06:34:19 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

bool	ft_cd(t_ctrl *ctrl, char *path)
{
	errno;
	char	buffer[4096];

	if (chdir(path) == -1)
		return (false);
		//if (errno == EACCES)
		//	return (false);		//perror Permission Denied
		//if (errno == ENOTDIR)
		//	return (false);		//perror Is not a directory
		//if (errno == ENOENT)
		//	return (false);		//perror Directory not exist
		//if (errno == EFAULT)
		//	return (false);		//perror Cant acces in this memory adress
		//if (errno == EIO)
		//	return (false);		//perror An I/O error appens
		//if (errno == ENAMETOOLONG)
		//	return (false);		//perror Path is too long
	else
	{
		ctrl->pwd = getcwd(buffer, 4096);
		return (true);
	}
	return (false);
}
