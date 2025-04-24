# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ticasali <ticasali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 01:28:43 by ticasali          #+#    #+#              #
#    Updated: 2025/04/25 01:28:49 by ticasali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				minishell

DIR_SRCS =			src

SRCS =				$(DIR_SRCS)/main.c 				\

DIR_OBJS =			.objs

OBJS =				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)

CFLAGS =			-Wall -Wextra -Werror

all:				$(NAME)

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c include/minishell.h
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@ -I./include

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) -o $@ $^ -I./include

clean:
					$(RM) -r $(DIR_OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean
					$(MAKE) all

.PHONY:				all clean fclean re