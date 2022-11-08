# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: greita <greita@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 19:03:16 by greita            #+#    #+#              #
#    Updated: 2022/11/08 20:22:48 by greita           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -I $(HEADER)

# check your version of readline
READLINE 	=	-lreadline \
				-L/usr/local/Cellar/readline/8.2.1/lib \
				-I/usr/local/Cellar/readline/8.2.1/include/readline

SRCS		=	main.c \
				parser/parse_execute.c \
				parser/launcher.c \
				parser/redirects_cut_off.c \
				parser/redirect_in_out_app.c \
				parser/redirect_heredoc_and_utils.c \
				parser/redirect_utils.c \
				parser/free_all.c \
				parser/run_execve.c \
				parser/run_cmd.c \
				parser/replace_var.c \
				parser/std_fd.c \
				parser/get_arg.c \
				parser/wildcard.c \
				parser/quotes.c \
				parser/signals.c \
				builtins/builtins.c \
				builtins/builtins_utils.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/export_utils2.c \
				builtins/unset.c \
				builtins/env.c \
				builtins/cd.c \
				builtins/cd_utils.c \
				builtins/cd_utils2.c \
				builtins/pwd.c \
				builtins/echo.c \
				builtins/exit.c

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)/minishell.h
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all

.PHONY		:	all clean fclean re
