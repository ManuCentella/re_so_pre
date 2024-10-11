/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:31:07 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/11 16:19:07 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_so_long.h"

// Función para cerrar la ventana del juego y salir del programa
int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

// Función para manejar las pulsaciones de teclas
int handle_keypress(int keycode, t_game *game)
{
    int new_x = game->info.player_x;
    int new_y = game->info.player_y;

    // Si se presiona la tecla Esc (código 65307), cerrar la ventana
    if (keycode == 65307) return close_window(game), 0;

    // Actualizar la posición del jugador según la tecla presionada
    update_position(keycode, &new_x, &new_y, game);

    // Verificar si el movimiento es válido
    if (is_valid_move(new_x, new_y, game))
        move_player(game, new_x, new_y);
    else
        printf("Movimiento fuera de los límites o en una pared: new_x = %d, new_y = %d\n", new_x, new_y);

    return 0;
}

// Función para actualizar la posición del jugador según la tecla presionada
void update_position(int keycode, int *new_x, int *new_y, t_game *game)
{
    if (keycode == 119) (*new_y)--; // W key
    else if (keycode == 115) (*new_y)++; // S key
    else if (keycode == 97) { (*new_x)--; game->img_player = game->img_playerleft; } // A key
    else if (keycode == 100) { (*new_x)++; game->img_player = game->img_player_original; } // D key
}

// Función para verificar si el movimiento es válido
int is_valid_move(int new_x, int new_y, t_game *game)
{
    return new_y >= 0 && new_y < game->info.height && new_x >= 0 && new_x < game->info.width && game->info.map[new_y][new_x] != '1';
}

// Función para actualizar la posición del jugador en el mapa
void update_player_position(t_game *game, int new_x, int new_y)
{
    // Redibujar la casilla anterior como vacía
    draw_tile(game, game->info.player_x, game->info.player_y, '0');
    // Actualizar el mapa
    game->info.map[game->info.player_y][game->info.player_x] = '0';
    game->info.map[new_y][new_x] = 'P';
    game->info.player_x = new_x;
    game->info.player_y = new_y;
    // Redibujar la nueva posición del jugador
    draw_tile(game, new_x, new_y, 'P');
}

// Función para manejar la recolección de coleccionables
void handle_collectible(t_game *game, int new_x, int new_y)
{
    if (game->info.map[new_y][new_x] == 'C')
    {
        game->info.num_collectibles--;
        printf("Coleccionables restantes: %d\n", game->info.num_collectibles);
        if (game->info.num_collectibles == 0)
        {
            printf("Todos los coleccionables recogidos! Ahora puedes salir.\n");
            game->info.exit_open = 1; // Cambiar a 1 (abierto)
            draw_tile(game, game->info.exit_x, game->info.exit_y, 'E');
        }
    }
}

// Función para manejar la entrada en la salida
void handle_exit(t_game *game, int new_x, int new_y)
{
    if (game->info.map[new_y][new_x] == 'E' && game->info.exit_open)
    {
        printf("Felicidades! Has completado el nivel.\n");
        exit(0); // Terminar el juego con éxito
    }
}

// Función para iniciar el bucle principal del juego
void start_game_loop(t_game *game)
{
    mlx_loop(game->mlx);
}