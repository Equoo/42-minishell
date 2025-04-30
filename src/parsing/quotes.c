/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:08 by dderny            #+#    #+#             */
/*   Updated: 2025/04/30 20:33:05 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1);
	}
	return (0);
}