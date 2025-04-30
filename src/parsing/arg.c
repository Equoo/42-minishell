/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/30 17:30:46 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

int	parse_arg(t_ctrl *ctrl, char *str, t_vector *args)
{
	char			*token;
	size_t			i;
	
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	token = sub_token(ctrl, str + i, &i, true);
	if (!token)
		return (-1);
	if (vec_append(args, &token))
		return (-1);
	return (i);
}
