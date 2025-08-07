# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/08/07 21:39:50 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -ldl -lglfw -pthread -lm

HDR = fdf.h

SRC = fdf.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_HDR = $(LIB_DIR)/libft.h

MLX_DIR = MLX42/build
MLX_NAME = $(MLX_DIR)//libmlx42.a
#MLX_HDR = $(MLX_DIR)/mlx.h

COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME)

debug: $(CFLAGS) += -g

$(NAME): $(OBJ) $(LIB_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_NAME) $(MLX_NAME)

$(OBJ_DIR)/%.o: %.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_NAME): $(LIB_HDR)
	@$(MAKE) -C $(LIB_DIR)

#$(MLX_NAME): $(MLX_HDR)
#	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@echo "$(COLOR) Cleaning $(NAME)$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all clean fclean re debug
