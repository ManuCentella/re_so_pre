/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:22:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/03 17:20:58 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

int	is_rectangular(t_info_map *info)
{
	int	y;

	y = 0;
	while (y < info->height)
	{
		if ((int)strlen(info->map[y]) != info->width)
		{
			fprintf(stderr, "Error: El mapa no es rectangular\n");
			return (EXIT_FAILURE);
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	is_surrounded_by_walls(t_info_map *info)
{
	int	x;
	int	y;

	x = 0;
	while (x < info->width)
	{
		if (info->map[0][x] != '1' || info->map[info->height - 1][x] != '1')
		{
			fprintf(stderr,
				"Error: El mapa no está cerrado/rodeado de muros\n");
			return (EXIT_FAILURE);
		}
		x++;
	}
	y = 0;
	while (y < info->height)
	{
		if (info->map[y][0] != '1' || info->map[y][info->width - 1] != '1')
		{
			fprintf(stderr,
				"Error: El mapa no está cerrado/rodeado de muros\n");
			return (EXIT_FAILURE);
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	count_map_elements(t_info_map *info, int *player_count, int *exit_count,
		int *collectible_count)
{
	int		y;
	int		x;
	char	tile;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			tile = info->map[y][x];
			if (tile == 'P')
				(*player_count)++;
			else if (tile == 'E')
				(*exit_count)++;
			else if (tile == 'C')
				(*collectible_count)++;
			else if (tile != '0' && tile != '1')
			{
				fprintf(stderr, "Error: Caracter inválido en el mapa: %c\n",
					tile);
				return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	has_valid_elements(int player_count, int exit_count, int collectible_count)
{
	if (player_count != 1)
	{
		fprintf(stderr,
			"Error: El mapa debe tener exactamente una posición inicial del jugador\n");
		return (EXIT_FAILURE);
	}
	if (exit_count != 1)
	{
		fprintf(stderr, "Error: El mapa debe tener exactamente una salida\n");
		return (EXIT_FAILURE);
	}
	if (collectible_count < 1)
	{
		fprintf(stderr,
			"Error: El mapa debe tener al menos un coleccionable\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_map(t_info_map *info)
{
	int player_count = 0;
	int exit_count = 0;
	int collectible_count = 0;

	if (is_rectangular(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (is_surrounded_by_walls(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (count_map_elements(info, &player_count, &exit_count,
			&collectible_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (has_valid_elements(player_count, exit_count,
			collectible_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// Verificar que haya un camino válido en el mapa (esto puede requerir una implementación adicional)

	return (EXIT_SUCCESS);
}
