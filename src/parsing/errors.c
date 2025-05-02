/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:17 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:55:07 by ticasali         ###   ########.fr       */
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
			"Minishell: %s: %s\n", path, strerror(errno));
	else if (c)
		ft_dprintf(STDERR_FILENO,
			"Minishell: Syntax error near unexpected token `%c'\n", c);
	return (1);
}
