/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:22:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/14 18:01:30 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

int	validate_map(t_info_map *info)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
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
	if (!is_valid_path(info, info->player_x, info->player_y))
	{
		fprintf(stderr, "Error: No hay un camino válido\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
	if (!check_horizontal_walls(info) || !check_vertical_walls(info))
	{
		fprintf(stderr, "Error: El mapa no está cerrado/rodeado de muros\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_horizontal_walls(t_info_map *info)
{
	int	x;

	x = 0;
	while (x < info->width)
	{
		if (info->map[0][x] != '1' || info->map[info->height - 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_vertical_walls(t_info_map *info)
{
	int	y;

	y = 0;
	while (y < info->height)
	{
		if (info->map[y][0] != '1' || info->map[y][info->width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}
