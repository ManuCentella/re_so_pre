/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:03:42 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 18:43:33 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	move_player(t_game *game, int new_x, int new_y)
{
	static int	move_count = 0;

	move_count++;
	ft_printf("Número de movimientos: %d\n", move_count);
	handle_collectible(game, new_x, new_y);
	handle_exit(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
}

void	init_game(t_info_map *info)
{
	init_info_map(info);
}

void	initialize_game(t_info_map *info, t_game *game, const char *map_file)
{
	init_info_map(info);
	if (get_map_dimensions(map_file, info) == EXIT_FAILURE)
	{
		ft_printf("Error: Failed to get map dimensions.\n");
		exit(EXIT_FAILURE);
	}
	if (read_map(map_file, info) == EXIT_FAILURE)
	{
		ft_printf("Error: Failed to read map.\n");
		exit(EXIT_FAILURE);
	}
	if (validate_map(info) == EXIT_FAILURE)
	{
		free_info_map(info);
		ft_printf("Error: Invalid map.\n");
		exit(EXIT_FAILURE);
	}
	game->info = *info;
}

void	start_game(t_game *game)
{
	init_mlx(game);
	load_images(game);
	draw_map(game);
	setup_events(game);
	start_game_loop(game);
}

int	main(int argc, char **argv)
{
	t_info_map info;
	t_game game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	initialize_game(&info, &game, argv[1]);
	start_game(&game);
	free_info_map(&info);
	return (EXIT_SUCCESS);
}
