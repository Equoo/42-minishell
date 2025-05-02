/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:54:09 by dderny            #+#    #+#             */
/*   Updated: 2025/05/03 00:16:52 by ticasali         ###   ########.fr       */
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

typedef bool	(*t_fchar)(char surrounder, char c);

typedef int		(*t_fparse)(t_ctrl *ctrl, char *str, t_command cmd);

int				token_error(char *path, char c);

char			*expand_all(t_ctrl *ctrl, char *str);
int				parse_expand(t_env *lst, char *key, size_t *len, char **value);

char			*sub_token(t_ctrl *ctrl, char *str, size_t *len, bool isexpand);

int				check_quotes(char c, char *surrounder, char *next_surrounder);

int				parse_redirection(t_ctrl *ctrl, char *str, t_command *cmd);
int				parse_pipe(t_ctrl *ctrl, char *str, t_command *cmd,
					t_vector *args);
int				parse_arg(t_ctrl *ctrl, char *str, t_vector *args);

int				parse_command(t_ctrl *ctrl, char *strcmd);

#endif