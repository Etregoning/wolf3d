# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/21 14:58:27 by etregoni          #+#    #+#              #
#    Updated: 2017/10/07 18:45:14 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CFLAGS = -Wall -Werror -Wextra -g

SRC_FILES = environment.c game_loop.c image.c key_hooks.c main.c \
			movement.c parse_map.c colors.c key_hooks2.c kane_alloc_wrap.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./include/
MLX_DIR = ./mlx/
LIBFT_DIR = ./libft/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
MLX = $(addprefix $(MLX_DIR), libmlx.a)
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

LINK = -L $(MLX_DIR) -L $(LIBFT_DIR) \
				-lmlx -lft -framework OpenGL -framework AppKit

all: obj $(LIBFT) $(MLX) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(CFLAGS) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<

$(LIBFT):
	@echo "\033[32mCompiling libft...\033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[1;4;32mlibft created.\033[0m"

$(MLX):
	@echo "\033[32mCompiling mlx...\033[0m"
	@make -C $(MLX_DIR)
	@echo "\033[1;4;32mmlx created.\033[0m"

$(NAME): $(OBJ)
	@echo "\033[32mCompiling $(NAME)...\033[0m"
	@gcc $(OBJ) $(LINK) -lm -o $(NAME)
	@echo "\033[1;4;32m$(NAME) Created.\033[0m"

clean:
	@echo "\033[31mRemoving objects...\033[0m"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "\033[1;4;31mObjects removed!\033[0m"

fclean: clean
	@echo "\033[31mRemoving $(NAME)...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[1;4;31m$(NAME) removed!\033[0m"

re: fclean all

.PHONY: clean fclean all re
