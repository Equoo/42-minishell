/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:17 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 14:33:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ft_printf.h>

int	token_error(char *path, char c)
{
	if (path)
		ft_dprintf(STDERR_FILENO,
			"minishell: %s: %s\n", path, strerror(errno));
	else if (c)
		ft_dprintf(STDERR_FILENO,
			"minishell: Syntax error near unexpected token `%c'\n", c);
	return (-1);
}
