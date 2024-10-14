/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:31:07 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/14 16:32:27 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	start_game_loop(t_game *game)
{
	mlx_loop(game->mlx);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->info.player_x;
	new_y = game->info.player_y;
	if (keycode == 65307)
		return (close_window(game), 0);
	update_position(keycode, &new_x, &new_y, game);
	if (is_valid_move(new_x, new_y, game))
		move_player(game, new_x, new_y);
	else
		printf("Movimiento fuera de los límites o en una pared\n");
	return (0);
}

void	update_position(int keycode, int *new_x, int *new_y, t_game *game)
{
	if (keycode == 119)
		(*new_y)--;
	else if (keycode == 115)
		(*new_y)++;
	else if (keycode == 97)
	{
		(*new_x)--;
		game->img_player = game->img_playerleft;
	}
	else if (keycode == 100)
	{
		(*new_x)++;
		game->img_player = game->img_player_original;
	}
}

int	is_valid_move(int new_x, int new_y, t_game *game)
{
	return (new_y >= 0 && new_y < game->info.height && new_x >= 0
		&& new_x < game->info.width && game->info.map[new_y][new_x] != '1');
}
