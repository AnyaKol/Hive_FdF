# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/08/06 19:03:14 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/include -Imlx_linux -O3

HDR = fdf.h

SRC = fdf.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_HDR = $(LIB_DIR)/libft.h

COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_NAME)

$(OBJ_DIR)/%.o: %.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_NAME): $(LIB_HDR)
	@$(MAKE) -C $(LIB_DIR)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@echo "$(COLOR) Cleaning $(NAME)$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all clean fclean re
