/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:03:42 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/10 21:33:59 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Otras inclusiones y definiciones

void flood_fill(t_info_map *info, int x, int y, bool **visited)
{
    if (x < 0 || x >= info->width || y < 0 || y >= info->height || visited[y][x] || info->map[y][x] == '1')
        return;

    visited[y][x] = true;

    flood_fill(info, x + 1, y, visited);
    flood_fill(info, x - 1, y, visited);
    flood_fill(info, x, y + 1, visited);
    flood_fill(info, x, y - 1, visited);
}

int is_valid_path(t_info_map *info, int start_x, int start_y)
{
    bool **visited = malloc(info->height * sizeof(bool *));
    for (int i = 0; i < info->height; i++)
    {
        visited[i] = malloc(info->width * sizeof(bool));
        for (int j = 0; j < info->width; j++)
            visited[i][j] = false;
    }

    flood_fill(info, start_x, start_y, visited);

    for (int i = 0; i < info->height; i++)
    {
        for (int j = 0; j < info->width; j++)
        {
            if ((info->map[i][j] == 'E' || info->map[i][j] == 'C') && !visited[i][j])
            {
                for (int k = 0; k < info->height; k++)
                    free(visited[k]);
                free(visited);
                return 0; // No se encontró un camino válido
            }
        }
    }

    for (int i = 0; i < info->height; i++)
        free(visited[i]);
    free(visited);

    return 1; // Camino válido encontrado
}





void	move_player(t_game *game, int new_x, int new_y)
{
	static int move_count = 0; // Contador de movimientos
	move_count++;
	printf("Número de movimientos: %d\n", move_count);
	handle_collectible(game, new_x, new_y);
	handle_exit(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
}



void	set_initial_player_position(t_info_map *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (info->map[y][x] == 'P')
			{
				info->player_x = x;
				info->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_game(t_info_map *info)
{
	init_info_map(info);
}

int	main(int argc, char **argv)
{
	t_info_map	info;
	t_game		game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	init_info_map(&info);
	if (get_map_dimensions(argv[1], &info) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (read_map(argv[1], &info) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (validate_map(&info) == EXIT_FAILURE)
	{
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
