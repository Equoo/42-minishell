/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:01:24 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/01 08:11:46 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_select(char *str, char c)
{
	size_t	ct;

	ct = 0;
	while (str[ct] != '\0' && str[ct] != c)
		++ct;
	return (ct);
}
