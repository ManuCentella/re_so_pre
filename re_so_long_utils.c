/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/14 19:25:57 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

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

void	update_map_dimensions(char *line, int *width, int *height)
{
	if (*width == 0)
		*width = ft_strlen(line);
	(*height)++;
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
	while ((line = read_and_trim_line(fd)) != NULL)
	{
		update_map_dimensions(line, &width, &height);
		free(line);
	}
	close(fd);
	info->width = width;
	info->height = height;
	return (EXIT_SUCCESS);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("Error opening map file");
	return (fd);
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
		fprintf(stderr, "Error: El mapa no es rectangular\n");
		free(line);
		return (EXIT_FAILURE);
	}
	info->map[i] = line;
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

int	allocate_map_memory(t_info_map *info)
{
    info->map = malloc(info->height * sizeof(char *));
    if (!info->map)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el mapa\n");
        return (EXIT_FAILURE);
    }
    info->num_collectibles = 0; // Inicializar el conteo de coleccionables a 0
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