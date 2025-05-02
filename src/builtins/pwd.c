/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:43:59 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/02 20:28:57 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	ft_pwd(t_ctrl *ctrl, char **flag)
{
	char	*buffer;

	(void) ctrl;
	(void) flag;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	write(1, buffer, ft_strlen(buffer));
	return (0);
}
