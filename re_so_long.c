/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:03:42 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/14 16:05:06 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_so_long.h"

void set_initial_player_position(t_info_map *info) {
    int y = 0;
    while (y < info->height) {
        int x = 0;
        while (x < info->width) {
            if (info->map[y][x] == 'P') {
                info->player_x = x;
                info->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}

// Función para mover al jugador a una nueva posición
void move_player(t_game *game, int new_x, int new_y) {
    static int move_count = 0; // Contador de movimientos
    move_count++;
    printf("Número de movimientos: %d\n", move_count);
    handle_collectible(game, new_x, new_y);
    handle_exit(game, new_x, new_y);
    update_player_position(game, new_x, new_y);
}

// Función para inicializar el juego
void init_game(t_info_map *info) {
    init_info_map(info);
}

// Función principal del programa
int main(int argc, char **argv) {
    t_info_map info;
    t_game game;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (EXIT_FAILURE);
    }
    init_info_map(&info);
    if (get_map_dimensions(argv[1], &info) == EXIT_FAILURE) {
        return (EXIT_FAILURE);
    }
    if (read_map(argv[1], &info) == EXIT_FAILURE) {
        return (EXIT_FAILURE);
    }
    if (validate_map(&info) == EXIT_FAILURE) {
        free_info_map(&info);
        return (EXIT_FAILURE);
    }
    game.info = info;
    init_mlx(&game);
    load_images(&game);
    draw_map(&game);
    setup_events(&game);
    start_game_loop(&game);
    free_info_map(&info);
    return (EXIT_SUCCESS);
}