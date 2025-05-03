# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 01:28:43 by ticasali          #+#    #+#              #
#    Updated: 2025/05/03 17:21:00 by ticasali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				minishell

DIR_SRCS =			src

SRCS =				$(DIR_SRCS)/main.c 				\
					$(DIR_SRCS)/load_ctrl.c 			\
					$(DIR_SRCS)/get_signal.c 			\
					$(DIR_SRCS)/readline.c 			\
					$(DIR_SRCS)/get_path.c 			\
					$(DIR_SRCS)/commands/commands_exec.c 			\
					$(DIR_SRCS)/commands/commands_utils.c 			\
					$(DIR_SRCS)/commands/commands.c 			\
					$(DIR_SRCS)/commands/pipeline.c 			\
					$(DIR_SRCS)/environ/env_init.c 			\
					$(DIR_SRCS)/environ/env_to_array.c 			\
					$(DIR_SRCS)/environ/get_env.c 			\
					$(DIR_SRCS)/environ/length.c 			\
					$(DIR_SRCS)/environ/strdup.c 			\
					$(DIR_SRCS)/builtins/cd.c 			\
					$(DIR_SRCS)/builtins/echo.c 			\
					$(DIR_SRCS)/builtins/env.c 			\
					$(DIR_SRCS)/builtins/exit.c 			\
					$(DIR_SRCS)/builtins/export.c 			\
					$(DIR_SRCS)/builtins/export_tools.c 	\
					$(DIR_SRCS)/builtins/pwd.c 			\
					$(DIR_SRCS)/builtins/unset.c 			\
					$(DIR_SRCS)/parsing/parsing.c 			\
					$(DIR_SRCS)/parsing/errors.c 			\
					$(DIR_SRCS)/parsing/pipe.c 			\
					$(DIR_SRCS)/parsing/expand.c 			\
					$(DIR_SRCS)/parsing/redirection.c 		\
					$(DIR_SRCS)/parsing/secure_parsing.c 	\

DIR_OBJS =			.objs

OBJS =				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
DEPS = 				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.d)

-include $(DEPS)

CFLAGS =			-Wall -Wextra -Werror -MMD -g3 -I./include -I./libft/headers
LIBS =				-L./libft -lft -lreadline

all:				libft
					$(MAKE) -j $(nproc) $(NAME)

libft:
					@$(MAKE) -C libft debug

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJS) libft/libft.a
					$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
					$(MAKE) -C libft clean
					$(RM) -r $(DIR_OBJS)

fclean:				clean
					$(MAKE) -C libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re exec libft

.DEFAULT_GOAL = all

