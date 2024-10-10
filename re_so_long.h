/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:16:11 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/10 21:03:57 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RE_SO_LONG_H
#define RE_SO_LONG_H

#include <stdbool.h>
#include "libft/inc/get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TILE_SIZE 64

typedef struct s_info_map
{
    int         width;
    int         height;
    char        **map;
    int         player_x;
    int         player_y;
    int         num_collectibles;
    int         exit_x;
    int         exit_y;
    int         exit_open; // Usar un entero para rastrear si la salida está abierta
}               t_info_map;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_info_map  info;
    void        *img_wall;
    void        *img_collectible;
    void        *img_exit;
    void        *img_empty;
    void        *img_player;
    void        *img_playerleft;
    void        *img_player_original; // Añadir esta línea para la imagen original del jugador
}               t_game;

typedef struct
{
    int         x;
    int         y;
}               Point;

// Funciones de inicialización
void init_info_map(t_info_map *info);
void init_mlx(t_game *game);
void setup_events(t_game *game);

// Funciones de manejo del mapa
void free_info_map(t_info_map *info);
int get_map_dimensions(const char *filename, t_info_map *info);
int read_map(const char *filename, t_info_map *info);
int validate_map(t_info_map *info);
void set_initial_player_position(t_info_map *info);
void load_map(const char *filename, t_info_map *info);
void validate_map_and_set_position(t_info_map *info);

// Funciones de manejo del juego
int close_window(t_game *game);
int handle_keypress(int keycode, t_game *game);
void update_player_position(t_game *game, int new_x, int new_y);
void handle_collectible(t_game *game, int new_x, int new_y);
void handle_exit(t_game *game, int new_x, int new_y);
void move_player(t_game *game, int new_x, int new_y);
void update_position(int keycode, int *new_x, int *new_y, t_game *game);
int is_valid_move(int new_x, int new_y, t_game *game);
void start_game_loop(t_game *game);

// Funciones de validación del mapa
int is_rectangular(t_info_map *info);
int is_surrounded_by_walls(t_info_map *info);
int process_tile(char tile, int *player_count, int *exit_count, int *collectible_count);
int has_valid_elements(int player_count, int exit_count, int collectible_count);
int count_map_elements(t_info_map *info, int *player_count, int *exit_count, int *collectible_count);
void flood_fill(t_info_map *info, int x, int y, bool **visited);
int is_valid_path(t_info_map *info, int start_x, int start_y);

// Funciones de gráficos
void load_images(t_game *game);
void *load_image(void *mlx, const char *path, int *width, int *height);
void *get_tile_image(t_game *game, char tile);
void draw_tile(t_game *game, int x, int y, char tile);
void draw_map(t_game *game);

#endif // RE_SO_LONG_H