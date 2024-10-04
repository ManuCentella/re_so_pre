/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:16:11 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/02 21:24:54 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RE_SO_LONG_H
# define RE_SO_LONG_H


#include "libft/inc/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
#include  <string.h>


# define TILE_SIZE 64

typedef struct s_info_map
{
    int width;
    int height;
    char **map;
    int player_x;
    int player_y;
    int num_collectibles;
    int exit_x;
    int exit_y;
    int exit_open; // Usar un entero para rastrear si la salida está abierta
} t_info_map;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_info_map info;
    void *img_wall;
    void *img_collectible;
    void *img_exit;
    void *img_empty;
    void *img_player;
} t_game;

void init_info_map(t_info_map *info);
void free_info_map(t_info_map *info);
int get_map_dimensions(const char *filename, t_info_map *info);
int read_map(const char *filename, t_info_map *info);
int close_window(t_game *game);
void load_images(t_game *game);
void draw_map(t_game *game);
char	*get_next_line(int fd);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
int handle_keypress(int keycode, t_game *game);
void update_player_position(t_game *game, int new_x, int new_y);
void handle_collectible(t_game *game, int new_x, int new_y);
void handle_exit(t_game *game, int new_x, int new_y);
void move_player(t_game *game, int new_x, int new_y);
int validate_map(t_info_map *info);

#endif