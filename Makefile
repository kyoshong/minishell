# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 17:43:53 by ulee              #+#    #+#              #
#    Updated: 2021/12/18 16:10:57 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -Wall -Wextra -Werror
CFLAGS = -lreadline -L/Users/ulee/.brew/opt/readline/lib -I/Users/ulee/.brew/opt/readline/include
INCS = -I./src/libft -I./ -I/Users/ulee/.brew/opt/readline/include
LIBFT = -L./src/libft -lft
RM = rm -f

FILE =	main \
		signal/sig_handler \
		builtin/builtin_cd \
		builtin/builtin_echo \
		builtin/builtin_env \
		builtin/builtin_export \
		builtin/builtin_getenv \
		builtin/builtin_pwd \
		builtin/builtin_unset \
		builtin/builtin_exit \
		execute/execute_bin \
		execute/execute_builtin \
		execute/execute_cmd \
		execute/execute_wildcard \
		execute/execute_make_arr \
		execute/execute_run_paths \
		exit/free_exit \
		exit/print_error \
		iohandler/pipe_handler \
		iohandler/redir_handler \
		iohandler/set_redir_fd \
		parsing/parsing_bundles \
		parsing/parsing_tokens \
		parsing/parsing_str \
		parsing/set_token \
		utils/list_utils \
		utils/list_utils2 \
		utils/str_utils \
		utils/split_utils \
		utils/fd_utils \
		utils/token_utils \
		utils/check_utils \
		signal/signal

SRCS = $(addprefix ./src/, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./src/, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)
$(NAME) : $(OBJS)
	make -C ./src/libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@
	@echo "\033[31m⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣷⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\033[33m⠀⠀⠀⠀⠀⠀⠀⣀⣶⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣦⣀⡀⠀⢀⣴⣇⠀⠀⠀⠀"
	@echo "\033[32m⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[34m⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[35m⠀⠀⠀⣴⣿⣿⣿⣿⠛⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀"
	@echo "\033[37m⠀⠀⣾⣿⣿⣿⣿⣿⣶⣿⣯⣭⣬⣉⣽⣿⣿⣄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀"
	@echo "\033[31m⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄"
	@echo "\033[33m⢸⣿⣿⣿⣿⠟⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⣿⣿⣿⣿⡿⠛⠉⠉⠉⠉⠁"
	@echo "\033[32m⠘⠛⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠃⠀⠀⠀⠀⠀"

clean:
	make -C ./src/libft clean
	$(RM) $(OBJS)
	$(RM) ./src/test.o

fclean: clean
	make -C ./src/libft fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
