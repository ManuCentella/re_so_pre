/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/15 18:32:36 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_and_trim_line(int fd)
{
	char	*line;
	int		line_length;

	line = get_next_line(fd);
	if (line)
	{
		line_length = ft_strlen(line);
		if (line[line_length - 1] == '\n')
			line[line_length - 1] = '\0';
	}
	return (line);
}

int	get_map_dimensions(const char *filename, t_info_map *info)
{
	int		fd;
	int		width;
	int		height;
	char	*line;

	fd = open_file(filename);
	if (fd == -1)
		return (EXIT_FAILURE);
	width = 0;
	height = 0;
	line = read_and_trim_line(fd);
	while (line != NULL)
	{
		update_map_dimensions(line, &width, &height);
		free(line);
		line = read_and_trim_line(fd);
	}
	close(fd);
	info->width = width;
	info->height = height;
	return (EXIT_SUCCESS);
}

int	read_and_validate_line(int fd, t_info_map *info, int i)
{
	char	*line;
	int		line_length;

	line = get_next_line(fd);
	if (!line)
		return (EXIT_FAILURE);
	line_length = ft_strlen(line);
	if (line[line_length - 1] == '\n')
		line[line_length - 1] = '\0';
	if (ft_strlen(line) != (size_t)info->width)
	{
		ft_printf("Error: El mapa no es rectangular\n");
		free(line);
		return (EXIT_FAILURE);
	}
	info->map[i] = line;
	return (EXIT_SUCCESS);
}

int	read_map(const char *filename, t_info_map *info)
{
	int	fd;

	fd = open_file(filename);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (allocate_map_memory(info) == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	if (read_map_lines(fd, info) == EXIT_FAILURE)
	{
		free_info_map(info);
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	read_map_lines(int fd, t_info_map *info)
{
	int	i;

	i = 0;
	while (i < info->height)
	{
		if (read_and_validate_line(fd, info, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		count_collectibles_and_store_coordinates(info, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
