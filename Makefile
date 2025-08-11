# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/08/11 12:57:04 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra # -Wunreachable-code -Ofast
INCFLAGS = $(addprefix -I, $(LIB_DIR) $(MLX_HDR))
LINKDIR = $(addprefix -L, $(LIB_DIR) $(MLX_DIR)/build)
LINKFLAGS = $(addprefix -l, ft mlx42) -ldl -lglfw -pthread -lm

HDR = fdf.h

SRC = \
	fdf.c \
	utils.c \
	args.c \
	map.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ------------  LIBFT  ------------------------------------------------------- #
LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a

# ------------  MLX  --------------------------------------------------------- #
MLX_DIR = MLX42
MLX_NAME = $(MLX_DIR)/build/libmlx42.a
MLX_HDR = $(MLX_DIR)/include

# ------------  COLORS  ------------------------------------------------------ #
COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME)

debug: $(CFLAGS) += -g

$(NAME): $(OBJ) $(LIB_NAME) $(MLX_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINKDIR) $(LINKFLAGS)

$(OBJ_DIR)/%.o: %.c $(HDR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $<

$(LIB_NAME):
	@$(MAKE) -C $(LIB_DIR)

$(MLX_NAME):
	$(MAKE) -C $(MLX_DIR)/build

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR) Cleaning $(NAME)$(RESET)"

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(MLX_NAME)$(RESET)"
	@$(MAKE) clean -C $(MLX_DIR)/build
	@echo "$(COLOR) Removing $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all clean fclean re debug
