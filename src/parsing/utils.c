/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:53:53 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 17:01:18 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isbashspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	check_quotes(char c, char *surrounder, char *next_surrounder)
{
	if (!*next_surrounder)
		*surrounder = 0;
	if (c == '\'' || c == '"')
	{
		if (*surrounder == 0)
		{
			*surrounder = c;
			*next_surrounder = c;
		}
		else if (*surrounder == c)
			*next_surrounder = 0;
	}
	return (1);
}
