# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 15:02:26 by akolupae          #+#    #+#              #
#    Updated: 2025/08/12 12:16:16 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra
INCFLAGS = $(addprefix -I, $(LIB_DIR) $(MLX_HDR) . /usr/include) -O3
LINKDIR = $(addprefix -L, $(LIB_DIR) $(MLX_DIR) /usr/lib)
LINKFLAGS = $(addprefix -l, ft mlx_Linux) -lXext -lX11 -lm -lz

HDR = fdf.h

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
	fdf.c \
	utils.c \
	args.c \
	map.c \
	visuals.c \
	)

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ------------  LIBFT  ------------------------------------------------------- #
LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a

# ------------  MLX  --------------------------------------------------------- #
MLX_DIR = minilibx-linux
MLX_NAME = $(MLX_DIR)/libmlx_Linux.a
MLX_HDR = $(MLX_DIR)

# ------------  COLORS  ------------------------------------------------------ #
COLOR = \033[1;32m
RESET = \033[0m

all: $(NAME)

debug: CFLAGS += -g
debug: all

$(NAME): $(OBJ) $(LIB_NAME) $(MLX_NAME)
	@echo "$(COLOR) Building $@$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINKDIR) $(LINKFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $<

$(LIB_NAME):
	@$(MAKE) -C $(LIB_DIR)

$(MLX_NAME):
	$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR) Cleaning $(NAME)$(RESET)"

fclean: clean
	@echo "$(COLOR) Removing $(LIB_NAME)$(RESET)"
	@rm -f $(LIB_NAME)
	@echo "$(COLOR) Removing $(MLX_NAME)$(RESET)"
	@$(MAKE) clean -C $(MLX_DIR)
	@echo "$(COLOR) Removing $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all clean fclean re debug
