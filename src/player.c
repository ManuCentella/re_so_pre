/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:22:03 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 15:11:24 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/inc/ft_printf.h"


void	update_player_position(t_game *game, int new_x, int new_y)
{
	draw_tile(game, game->info.player_x, game->info.player_y, '0');
	game->info.map[game->info.player_y][game->info.player_x] = '0';
	game->info.map[new_y][new_x] = 'P';
	game->info.player_x = new_x;
	game->info.player_y = new_y;
	draw_tile(game, new_x, new_y, 'P');
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->info.map[new_y][new_x] == 'C')
	{
		game->info.num_collectibles--;
		ft_printf("Coleccionables restantes: %d\n", game->info.num_collectibles);
		if (game->info.num_collectibles == 0)
		{
			ft_printf("Todos los coleccionables recogidos! Ahora puedes salir.\n");
			game->info.exit_open = 1;
			draw_tile(game, game->info.exit_x, game->info.exit_y, 'E');
		}
	}
}

void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->info.map[new_y][new_x] == 'E' && game->info.exit_open)
	{
		ft_printf("Felicidades! Has completado el nivel.\n");
		exit(0);
	}
}
