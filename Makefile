# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 15:53:23 by hmateque          #+#    #+#              #
#    Updated: 2025/06/03 08:53:54 by lantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g

Libft_DIR = ./libft
Libft_A = $(Libft_DIR)/libft.a

Libix_DIR = ./mlx_linux
Libix_A = $(Libix_DIR)/libmlx.a


SRCS =	src/main.c\
		src/exit.c\
		src/map_render/evennts_player.c\
		src/map_render/init_window.c\
		src/map_render/manipulate_pixels.c\
		src/map_render/mini_map_aux.c\
		src/map_render/mini_map.c\
		src/map_render/move_player.c\
		src/map_render/player_placement.c\
		src/map_render/render_core_aux.c\
		src/map_render/render_core.c\
		src/map_render/render.c\
		src/parser/parse_colors.c\
		src/parser/parse_file.c\
		src/parser/parse_map.c\
		src/parser/parse_position.c\
		src/parser/parse_textures.c\
		src/parser/validator_aux.c\
		src/parser/validator_colors.c\
		src/parser/validator_config.c\
		src/parser/validator_map_aux.c\
		src/parser/validator_map.c\
		src/parser/validator_texture.c\



OBJ_SRC = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(Libft_A) $(Libix_A) $(OBJ_SRC)  
	@$(CC) $(FLAGS) $(OBJ_SRC) $(Libft_A) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(Libix_A):
	@$(MAKE) -C $(Libix_DIR)

$(Libft_A):
	@$(MAKE) -C $(Libft_DIR)


%.o: %.c
	@$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJ_SRC)
	$(MAKE) clean -C $(Libft_DIR)
	$(MAKE) clean -C $(Libix_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(Libft_DIR)

re: fclean all

test:
	./test_maps.sh

start:
	./$(NAME) maps/valid/subject.cub

valgrind:
	valgrind --leak-check=full ./$(NAME) maps/valid/subject.cub

valgrind_leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/valid/subject.cub

.PHONY: all clean fclean re
