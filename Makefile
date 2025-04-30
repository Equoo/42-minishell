# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 01:28:43 by ticasali          #+#    #+#              #
#    Updated: 2025/04/30 16:38:17 by ticasali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				minishell

DIR_SRCS =			src

SRCS =				$(DIR_SRCS)/main.c 				\
					$(DIR_SRCS)/compare.c 			\
					$(DIR_SRCS)/concat.c			\
					$(DIR_SRCS)/convert.c 			\
					$(DIR_SRCS)/env.c				\
					$(DIR_SRCS)/export.c			\
					$(DIR_SRCS)/length.c			\
					$(DIR_SRCS)/lst_init.c			\
					$(DIR_SRCS)/print.c				\
					$(DIR_SRCS)/strdup.c 			\
					$(DIR_SRCS)/unset.c 			\

PIPEX_SRCS =		$(DIR_SRCS)/pipex.c 				\
					$(DIR_SRCS)/commands/commands.c			\
					$(DIR_SRCS)/commands/commands_utils.c	\
					$(DIR_SRCS)/commands/commands_exec.c	\

DIR_OBJS =			.objs

OBJS =				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
DEPS = 				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.d)

ifdef MODE
	ifeq ($(MODE), pipex)
		NAME =			pipex
		SRCS =				$(PIPEX_SRCS)
		OBJS =				$(PIPEX_SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
		DEPS = 				$(PIPEX_SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.d)
	endif
endif

-include $(DEPS)

CFLAGS =			-Wall -Wextra -Werror -lreadline -MMD -g3 -I./include 
#-I./libft/headers
#LIBS =			-L./libft -lft

all:				#libft
					$(MAKE) -j $(nproc) $(NAME)

#libft:
#					@$(MAKE) -C libft

exec:
					$(MAKE) MODE=pipex

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) -o $@ $^
#  $(LIBS)

clean:
#					$(MAKE) -C libft clean
					$(RM) -r $(DIR_OBJS)

fclean:				clean
#					$(MAKE) -C libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re exec
#libft

.DEFAULT_GOAL = all

