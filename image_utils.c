/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:38:16 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/11 16:21:03 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

// Función para verificar que las imágenes tengan el tamaño correcto
void verify_image_size(int width, int height)
{
    if (width != TILE_SIZE || height != TILE_SIZE) {
        fprintf(stderr, "Error: Las imágenes deben tener el tamaño de TILE_SIZE\n");
        exit(EXIT_FAILURE);
    }
}

// Función para cargar todas las imágenes necesarias para el juego
void load_images(t_game *game)
{
    int img_width;
    int img_height;

    printf("Cargando imagenes...\n");

    // Cargar las imágenes y verificar su tamaño
    game->img_wall = load_image(game->mlx, "images/wall.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    game->img_empty = load_image(game->mlx, "images/empty.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    game->img_player = load_image(game->mlx, "images/player1.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    game->img_playerleft = load_image(game->mlx, "images/player1left.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    game->img_collectible = load_image(game->mlx, "images/collectible.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    game->img_exit = load_image(game->mlx, "images/exit.xpm", &img_width, &img_height);
    verify_image_size(img_width, img_height);

    // Asignar la imagen original del jugador
    game->img_player_original = game->img_player;

    printf("Imagenes cargadas correctamente\n");
}