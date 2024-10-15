/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:11 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 13:00:56 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_info_map *info, int x, int y, bool **visited)
{
	if (x < 0 || x >= info->width || y < 0 || y >= info->height || visited[y][x]
		|| info->map[y][x] == '1')
		return ;
	visited[y][x] = true;
	flood_fill(info, x + 1, y, visited);
	flood_fill(info, x - 1, y, visited);
	flood_fill(info, x, y + 1, visited);
	flood_fill(info, x, y - 1, visited);
}

int	is_valid_path(t_info_map *info, int start_x, int start_y)
{
	bool	**visited;

	visited = allocate_visited(info->height, info->width);
	initialize_visited(visited, info->height, info->width);
	flood_fill(info, start_x, start_y, visited);
	if (!check_path(info, visited))
	{
		free_visited(visited, info->height);
		return (0);
	}
	free_visited(visited, info->height);
	return (1);
}

bool	**allocate_visited(int height, int width)
{
	bool	**visited;
	int		i;

	visited = malloc(height * sizeof(bool *));
	i = 0;
	while (i < height)
	{
		visited[i] = malloc(width * sizeof(bool));
		i++;
	}
	return (visited);
}

void	initialize_visited(bool **visited, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
}

int	check_path(t_info_map *info, bool **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			if ((info->map[i][j] == 'E' || info->map[i][j] == 'C')
				&& !visited[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	free_visited(bool **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
