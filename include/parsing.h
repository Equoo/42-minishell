/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:54:09 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 08:09:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "commands.h"
# include "environ.h"
# include "ft_vector.h"
# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_PIPE,
	TOKEN_RIN,
	TOKEN_ROUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ARG,
	TOKEN_VAR,
}				t_token_type;

int				token_error(char *path, char c);
char 			*get_expanded(t_ctrl *ctrl, char *str);

int				parse_redirection(t_ctrl *ctrl, char *operator, char *file, t_command *cmd);
int				parse_pipe(t_ctrl *ctrl, char *operator, t_command *cmd,
					t_vector *args);

int				parse_command(t_ctrl *ctrl, char *strcmd);

#endif
