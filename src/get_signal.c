/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:14:31 by ticasali          #+#    #+#             */
/*   Updated: 2025/05/03 09:45:11 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>

bool	set_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGPIPE);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGTSTP);
	sigaddset(&sa.sa_mask, SIGSYS);
	sigaddset(&sa.sa_mask, SIGABRT);
	sigaddset(&sa.sa_mask, SIGCHLD);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	if ((sigaction(SIGPIPE, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGINT, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGTSTP, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGSYS, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGABRT, &sa, 0)) == -1)
		return (false);
	if ((sigaction(SIGCHLD, &sa, 0)) == -1)
		return (false);
	return (true);
}
