/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:14:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 17:32:28 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include "minishell.h"

void	handle_signal(int sig)
{
	g_sigval = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	no_handle_signal(int sig)
{
	(void)sig;
}

bool	set_signal(bool	check)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;
	if (check == true)
		sa.sa_handler = handle_signal;
	if (check == false)
		sa.sa_handler = no_handle_signal;
	if ((sigaction(SIGQUIT, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGINT, &sa, 0)) == -1)
		return (false);
	return (true);
}
