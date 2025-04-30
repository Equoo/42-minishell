/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:43:59 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 00:42:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

void	ft_pwd(int fd)
{
	char	*buffer;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("getcwd");
		return;
	}
	write(fd, buffer, ft_strlen(buffer));
}
