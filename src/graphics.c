/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:52:39 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 14:39:10 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
# include "libft/inc/ft_printf.h"


void	*load_image(void *mlx, const char *file_path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, (char *)file_path, width, height);
	if (!img)
	{
		ft_printf("Error al cargar %s\n", file_path);
		exit(EXIT_FAILURE);
	}
	return (img);
}

void	process_keypress(int keycode, int *new_x, int *new_y)
{
	if (keycode == 119)
		(*new_y)--;
	else if (keycode == 115)
		(*new_y)++;
	else if (keycode == 97)
		(*new_x)--;
	else if (keycode == 100)
		(*new_x)++;
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->info.height)
	{
		x = 0;
		while (x < game->info.width)
		{
			draw_tile(game, x, y, game->info.map[y][x]);
			x++;
		}
		y++;
	}
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
	{
		if (game->info.num_collectibles == 0)
			img = game->img_exit;
		else
			img = game->img_empty;
	}
	else
		img = game->img_empty;
	put_image_to_window(game, img, x, y);
}

int	process_tile(char tile, int *player_count, int *exit_count,
		int *collectible_count)
{
	if (tile == 'P')
		(*player_count)++;
	else if (tile == 'E')
		(*exit_count)++;
	else if (tile == 'C')
		(*collectible_count)++;
	else if (tile != '0' && tile != '1')
	{
		ft_printf("Error: Caracter inválido en el mapa: %c\n", tile);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	put_image_to_window(t_game *game, void *img, int x, int y)
{
	if (img)
	{
		mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
			* TILE_SIZE);
	}
	else
	{
		ft_printf("Error: Imagen nula en draw_tile\n");
		exit(EXIT_FAILURE);
	}
}
