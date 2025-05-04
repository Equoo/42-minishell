/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:54:09 by dderny            #+#    #+#             */
/*   Updated: 2025/05/04 10:31:12 by ticasali         ###   ########.fr       */
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
char			*get_expanded(t_ctrl *ctrl, char *str, char quotes[2]);

int				parse_redirection(t_ctrl *ctrl, char *operator,
					char *file, t_command *cmd);
int				parse_pipe(t_ctrl *ctrl, char *operator, t_command *cmd,
					t_vector *args);

int				parse_command(t_ctrl *ctrl, char *strcmd);

void			vector_expand(t_ctrl *ctrl, char *str, t_vector outstr);
int				check_quotes(char c, char *surrounder, char *next_surrounder);
int				array_expand_all(t_ctrl *ctrl, t_vector array);
int				get_expand(t_ctrl *ctrl, char *key,
					size_t *out_len, char **value);
size_t			skip_backslash(char quotes[2], size_t i, char *str);
int				last_command(t_command cmd, t_ctrl *ctrl, t_vector args);
int				vec_secure(t_vector *vec, char *val);
char			*heredoc_expand(t_ctrl *ctrl, char *str);
int				ft_isexpand(char c);

char			*chunk_expand(t_ctrl *ctrl, char *str);

t_vector		secure_expand_operators(char *str);

#endif
