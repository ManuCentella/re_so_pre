/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:52:39 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/10 21:33:41 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

void	draw_map(t_game *game)
{
    void	*img;
    int x, y;

    for (y = 0; y < game->info.height; y++)
    {
        for (x = 0; x < game->info.width; x++)
        {
            img = get_tile_image(game, game->info.map[y][x]);
            mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

void	*get_tile_image(t_game *game, char tile)
{
    if (tile == '1')
        return (game->img_wall);
    else if (tile == 'P')
    {
        if (game->img_player == NULL)
        {
            fprintf(stderr, "Error: Imagen del jugador es nula\n");
            exit(EXIT_FAILURE);
        }
        printf("Dibujando jugador\n");
        return (game->img_player);
    }
    else if (tile == 'C')
    {
        if (game->img_collectible == NULL)
        {
            fprintf(stderr, "Error: Imagen del coleccionable es nula\n");
            exit(EXIT_FAILURE);
        }
        printf("Dibujando coleccionable\n");
        return (game->img_collectible);
    }
    else
        return (game->img_empty);
}

void	draw_tile(t_game *game, int x, int y, char tile)
{
    void	*img;

    if (tile == '0')
        img = game->img_empty;
    else if (tile == 'P')
        img = game->img_player;
    else if (tile == '1')
        img = game->img_wall;
    else if (tile == 'C')
        img = game->img_collectible;
    else if (tile == 'E')
        img = game->img_exit;
    else
        img = game->img_empty;
    // Verifica que la imagen no sea nula antes de dibujarla
    if (img)
    {
        mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
    }
    else
    {
        fprintf(stderr, "Error: Imagen nula en draw_tile\n");
    }
}

void *load_image(void *mlx, const char *file_path, int *width, int *height)
{
    void *img = mlx_xpm_file_to_image(mlx, (char *)file_path, width, height);
    if (!img) {
        fprintf(stderr, "Error al cargar %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return img;
}

void	process_keypress(int keycode, int *new_x, int *new_y)
{
	if (keycode == 119) // W key
		(*new_y)--;
	else if (keycode == 115) // S key
		(*new_y)++;
	else if (keycode == 97) // A key
		(*new_x)--;
	else if (keycode == 100) // D key
		(*new_x)++;
}

