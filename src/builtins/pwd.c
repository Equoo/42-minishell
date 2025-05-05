/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:43:59 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 03:38:09 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	ft_pwd(t_ctrl *ctrl, char **flag, int fd)
{
	char	*buffer;

	(void) ctrl;
	(void) flag;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("minishell: pwd");
		return (-1);
	}
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	free(buffer);
	return (0);
}
