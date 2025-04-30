/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:32:08 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 21:17:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdbool.h>
#include <unistd.h>

void	ft_echo(char *str, int fd, bool	flag)
{
	write(fd, str, ft_strlen(str));
	if (flag == true)
		write(fd, "\n", 1);
}