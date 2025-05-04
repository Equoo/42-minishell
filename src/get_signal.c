/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:14:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/04 23:00:08 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

static void	disable_echoctl(bool not )
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("minishell: tcgetattr");
		return ;
	}
	if (not)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("minishell: tcsetattr");
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sigval = 2;
		write(STDOUT_FILENO, "-->^C", 5);
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
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
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
}

bool	set_signal(bool check)
{
	struct sigaction	sa;

	disable_echoctl(check);
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
