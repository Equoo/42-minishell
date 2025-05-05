/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:14:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/05 08:40:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <libft.h>

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
		if (rl_prompt)
			write(STDOUT_FILENO, rl_prompt, ft_strlen(rl_prompt));
		if (rl_line_buffer)
			write(STDOUT_FILENO, rl_line_buffer, ft_strlen(rl_line_buffer));
		write(STDOUT_FILENO, "^C", 2);
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

void	heredoc_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sigval = 2;
		rl_done = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}

bool	set_signal(int check)
{
	struct sigaction	sa;

	disable_echoctl(check);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGPIPE);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	if (check == 1)
		sa.sa_handler = handle_signal;
	if (check == 0)
		sa.sa_handler = no_handle_signal;
	if (check == 2)
		sa.sa_handler = heredoc_handle_signal;
	if ((sigaction(SIGQUIT, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGPIPE, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGINT, &sa, 0)) == -1)
		return (false);
	return (true);
}
