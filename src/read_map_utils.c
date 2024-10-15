/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:29:43 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 18:32:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_info_map(t_info_map *info)
{
	int	i;

	i = 0;
	while (i < info->height)
	{
		free(info->map[i]);
		i++;
	}
	free(info->map);
}
void	update_map_dimensions(char *line, int *width, int *height)
{
	if (*width == 0)
		*width = ft_strlen(line);
	(*height)++;
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("Error opening map file");
	return (fd);
}

int	allocate_map_memory(t_info_map *info)
{
	info->map = malloc(info->height * sizeof(char *));
	if (!info->map)
	{
		ft_printf("Error: No se pudo asignar memoria para el mapa\n");
		return (EXIT_FAILURE);
	}
	info->num_collectibles = 0;
	return (EXIT_SUCCESS);
}

void	count_collectibles_and_store_coordinates(t_info_map *info, int i)
{
	int	j;

	j = 0;
	while (j < info->width)
	{
		if (info->map[i][j] == 'C')
			info->num_collectibles++;
		else if (info->map[i][j] == 'E')
		{
			info->exit_x = j;
			info->exit_y = i;
		}
		else if (info->map[i][j] == 'P')
		{
			info->player_x = j;
			info->player_y = i;
		}
		j++;
	}
}
