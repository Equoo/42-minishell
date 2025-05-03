/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:27:37 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 07:10:05 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"
#include "libft.h"

short	ft_atos(char *str)
{
	long	ret;
	int		sign;
	size_t	ct;

	sign = 1;
	ret = 0;
	ct = 0;
	if (str[ct] == '-' || str[ct] == '+')
		if (str[ct++] == '-')
			sign = -1;
	while (str[ct] > 47 && str[ct] < 58)
	{
		ret += str[ct] - 48;
		if ((str[++ct] > 47 && str[ct] < 58))
			ret *= 10;
	}
	return ((short)(ret * sign));
}

bool	check_ascii(char *str)
{
	size_t	ct;
	size_t	check;

	ct = 0;
	check = 0;
	if (str[ct] != '-' && str[ct] != '+' && (str[ct] < 48 || str[ct] > 57))
		return (false);
	if ((str[ct] == '-' || str[ct] == '+')
		&& (str[ct + 1] < 48 || str[ct] > 57))
		return (false);
	if (str[ct] == '-' || str[ct] == '+')
		++ct;
	while (str[ct++] == '0')
		++check;
	while (str[ct] != '\0')
	{
		if (str[ct] < 48 || str[ct] > 57)
			return (false);
		++ct;
	}
	if ((ct - check) > 11)
		return (false);
	return (true);
}

int	ft_exit(t_ctrl *ctrl, char **flag)
{
	if (flag[1] == NULL)
	{
		ctrl->end = true;
		return (0);
	}
	if (check_ascii(flag[1]) == false)
	{
		ctrl->exit = 2;
		ctrl->end = true;
		return (-1);
	}
	ctrl->exit = ft_atos(flag[1]);
	ctrl->end = true;
	return (0);
}
