/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:12:26 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/10 20:17:38 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_so_long.h"

void init_info_map(t_info_map *info)
{
    info->width = 0;
    info->height = 0;
    info->map = NULL;
    info->player_x = 0;
    info->player_y = 0;
    info->num_collectibles = 0;
    info->exit_x = 0;
    info->exit_y = 0;
    info->exit_open = 0; // Inicializar exit_open a 0 (cerrado)
}

void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (game->mlx == NULL)
    {
        fprintf(stderr, "Error initializing MLX\n");
        free_info_map(&game->info);
        exit(EXIT_FAILURE);
    }
    game->win = mlx_new_window(game->mlx, game->info.width * TILE_SIZE,
            game->info.height * TILE_SIZE, "so_long");
    if (game->win == NULL)
    {
        fprintf(stderr, "Error creating window\n");
        free(game->mlx);
        free_info_map(&game->info);
        exit(EXIT_FAILURE);
    }
}

void setup_events(t_game *game)
{
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_key_hook(game->win, handle_keypress, game);
}