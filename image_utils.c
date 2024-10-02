/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:38:16 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/02 19:43:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

void *load_image(void *mlx, char *file_path, int *width, int *height)
{
    void *img = mlx_xpm_file_to_image(mlx, file_path, width, height);
    if (!img) {
        fprintf(stderr, "Error al cargar %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return img;
}

void verify_image_size(int width, int height)
{
    if (width != TILE_SIZE || height != TILE_SIZE) {
        fprintf(stderr, "Error: Las imágenes deben tener el tamaño de TILE_SIZE\n");
        exit(EXIT_FAILURE);
    }
}

void load_images(t_game *game)
{
    int img_width;
    int img_height;

    printf("Cargando imagenes...\n");

    game->img_wall = load_image(game->mlx, "images/wall.xpm", &img_width, &img_height);
    game->img_empty = load_image(game->mlx, "images/empty.xpm", &img_width, &img_height);
    game->img_player = load_image(game->mlx, "images/player1.xpm", &img_width, &img_height);
    game->img_collectible = load_image(game->mlx, "images/collectible.xpm", &img_width, &img_height);
    game->img_exit = load_image(game->mlx, "images/exit.xpm", &img_width, &img_height);

    verify_image_size(img_width, img_height);

    printf("Imagenes cargadas correctamente\n");
}
