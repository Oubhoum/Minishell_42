# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 09:44:35 by araiteb           #+#    #+#              #
#    Updated: 2023/10/21 13:24:36 by aoubhoum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc 
CFLAGS := -Wall -Wextra -Werror #-g -fsanitize=address
INCLUDE := minishell.h
SRCS := main.c  execution2.c fonction_libft.c char_size.c ft_split.c list.c ft_strtrim.c \
		syntaxe.c free.c execution.c file.c list2.c fonction_here_doc.c execution/exit.c execution/echo.c execution/pwd.c \
		execution/cd.c execution/unset.c  execution/env.c ft_itoa.c ft_atoi.c fontion_libft2.c\
		ft_lstnew.c get_cmd.c execution3.c execution4.c expand.c expand_norm.c env_remlissage.c ft_signals.c\
		execchile.c outi_exect.c ft_lstnew2.c ft_split2.c syntaxe2.c   execution/export.c\
		execution/export_tools2.c execution/expoet_tools.c execution/utils.c execution/ft_perror.c get_env_values.c\
		 execution/sort_env.c execution/export_tools3.c env_remlissage2.c synt.c\
 
OBJS := $(SRCS:.c=.o)
EXEC := minishell
COMP = ~/.brew/opt/readline/lib
LINK = ~/.brew/opt/readline/include

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline -L $(COMP)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(LINK) -c  $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re : fclean all
.PHONY: all clean fclean