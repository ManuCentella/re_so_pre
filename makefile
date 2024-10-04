# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 13:07:22 by mcentell          #+#    #+#              #
#    Updated: 2024/10/02 21:23:26 by mcentell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)/inc -I$(MLX_DIR) -fsanitize=address,leak

# Especificar los archivos fuente y los archivos objeto
SRCS = re_so_long.c re_so_long_utils.c image_utils.c validate_map.c
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
OBJS = $(SRCS:.c=.o)

# Nombre de la biblioteca estática
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Regla para compilar el programa
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Regla para compilar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar la biblioteca estática
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

# Regla para recompilar todo
re: fclean all

.PHONY: all clean fclean re