# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alechin <alechin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 17:34:40 by alechin           #+#    #+#              #
#    Updated: 2025/04/02 17:34:40 by alechin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(HEADER_DIRECTORY)

HEADER = $(HEADER_DIRECTORY)/pipex.h

HEADER_DIRECTORY = include
SOURCE_DIRECTORY = src

SOURCE = \
	src/execute.c	src/main.c		src/error.c		\

OBJECT = $(SOURCE:.c=.o)

LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_PATH = libft

DEFAULT = \033[1;39m
RESET = \033[0m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m

all: $(NAME)

$(SOURCE_DIRECTORY)%.o: $(SOURCE_DIRECTORY)%.c
	@echo "$(YELLOW)\nInitializing Pipex...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT) $(LIBFT)
	@echo "$(YELLOW)\nCompiling Pipex.c...$(RESET)"
	@echo "$(YELLOW)\nCompiling Execute.c...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECT) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)\nSuccessfully compiled pipex...$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)\nCompiling Libft.c...$(RESET)"
	@make -C $(LIBFT_PATH) all

clean:
	@clear
	@$(RM) $(OBJECT)
	@make -C $(LIBFT_PATH) clean
	@echo "$(CYAN)\nSuccessfully cleaned all object files...$(RESET)"

fclean: clean
	@clear
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(CYAN)\nSuccessfully cleaned all object & executable files...$(RESET)"

clear:
	@clear

re:
	clear fclean all

valgrind:
	valgrind --leak-check=full ---show-leak-kinds=all --track-origin=yes

.PHONY: all clean fclean re valgrind