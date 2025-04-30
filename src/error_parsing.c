/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:13:32 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/30 07:28:25 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_parsing(char	*str)
{
	if (check_end_command(str) == false)
		return (false);
	if (check_single_quote(str) == false)
		return (false);
	if (check_double_quote(str) == false)
		return (false);
	if (check_quote_combine(str) == false)
		return (false);
	return (true);
}

bool	check_end_command(char *str)
{
	size_t	ct;

	ct = 0;
	while (str[ct] != '\0')
		++ct;
	while (ct != 0 && str[ct] == ' ')
		--ct;
	if (str[ct] == '|' || str[ct] == '<' || str[ct] == '>')
		return (false);
	return (true);
}

bool	check_single_quote(char *str)
{
	size_t	ct;
	size_t	ct_quote;

	ct = 0;
	ct_quote = 0;
	while (str[ct] != '\0')
	{
		if (str[ct] == 39)
			++ct_quote;
		++ct;
	}
	if (ct_quote % 2 == 0)
		return (true);
	return (false);
}

bool	check_double_quote(char *str)
{
	size_t	ct;
	size_t	ct_quote;

	ct = 0;
	ct_quote = 0;
	while (str[ct] != '\0')
	{
		if (str[ct] == '"')
			++ct_quote;
		++ct;
	}
	if (ct_quote % 2 == 0)
		return (true);
	return (false);
}

bool	check_quote_combine(char *str)
{
	size_t	ct;
	bool	simpl;
	bool	doubl;

	ct = 0;
	simpl = false;
	doubl = false;
	while (str[ct] != '\0')
	{
		if (str[ct] == 39)
		{
			if (simpl == false)
				simpl = true;
			else
				simpl = false;
			if (doubl == true)
				return (false);
		}
		if (str[ct] == '"')
		{
			if (doubl == false)
				doubl = true;
			else
				doubl = false;
			if (simpl == true)
				return (false);
		}
		++ct;
	}
	return (true);
}