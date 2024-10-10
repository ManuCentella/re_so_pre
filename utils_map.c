/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:00:58 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/10 20:25:44 by mcentell         ###   ########.fr       */
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

int is_surrounded_by_walls(t_info_map *info)
{
    int x = 0, y = 0;

    while (x < info->width || y < info->height)
    {
        if ((x < info->width && (info->map[0][x] != '1' || info->map[info->height - 1][x] != '1')) ||
            (y < info->height && (info->map[y][0] != '1' || info->map[y][info->width - 1] != '1')))
        {
            fprintf(stderr, "Error: El mapa no está cerrado/rodeado de muros\n");
            return (EXIT_FAILURE);
        }
        if (x < info->width) x++;
        if (y < info->height) y++;
    }
    return (EXIT_SUCCESS);
}

int process_tile(char tile, int *player_count, int *exit_count, int *collectible_count)
{
    if (tile == 'P')
        (*player_count)++;
    else if (tile == 'E')
        (*exit_count)++;
    else if (tile == 'C')
        (*collectible_count)++;
    else if (tile != '0' && tile != '1')
    {
        fprintf(stderr, "Error: Caracter inválido en el mapa: %c\n", tile);
        return (EXIT_FAILURE);
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
int count_map_elements(t_info_map *info, int *player_count, int *exit_count, int *collectible_count)
{
    int y = 0;
    int x;
    while (y < info->height)
    {
        x = 0;
        while (x < info->width)
        {
            if (process_tile(info->map[y][x], player_count, exit_count, collectible_count) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            x++;
        }
        y++;
    }
    return (EXIT_SUCCESS);
}