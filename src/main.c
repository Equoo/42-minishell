/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:06:04 by ticasali          #+#    #+#             */
/*   Updated: 2025/04/28 05:19:19 by ticasali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)(ac);
	(void)(av);
	t_env	*lst = lst_init(env);
	printf("---------%s\n", "ENV");
	ft_env(lst);
	printf("---------%s\n", "EXPORT NO ARG");
	ft_export_no_arg(lst);
	printf("---------%s\n", "EXPORT ARG");
	ft_export(lst, "Test", NULL);
	ft_env(lst);
	printf("---------%s\n", "EXPORT NO ARG");
	ft_export_no_arg(lst);
	printf("---------%s\n", "EXPORT PATH");
	ft_export(lst, "PATH", "Derriere toi");
	ft_env(lst);
	printf("---------%s\n", "UNSET");
	ft_unset(lst, "Test");
	ft_env(lst);
}