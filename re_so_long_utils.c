/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/01 18:55:09 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

void free_info_map(t_info_map *info)
{
    int i = 0;

    if (info->map != NULL)
    {
        while (info->map[i] != NULL)
        {
            free(info->map[i]);
            i++;
        }
        free(info->map);
    }
}

int get_map_dimensions(const char *filename, t_info_map *info)
{
    int fd;
    char *line;
    int width = 0;
    int height = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map file");
        return (EXIT_FAILURE);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        // Eliminar el carácter de nueva línea si está presente
        int line_length = ft_strlen(line);
        if (line[line_length - 1] == '\n')
            line[line_length - 1] = '\0';

        if (width == 0)
            width = ft_strlen(line);
        height++;
        free(line);
    }
    close(fd);
    info->width = width;
    info->height = height;
    return (EXIT_SUCCESS);
};


int read_map(const char *filename, t_info_map *info)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        return (EXIT_FAILURE);
    }

    info->map = malloc(info->height * sizeof(char *));
    if (!info->map)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el mapa\n");
        fclose(file);
        return (EXIT_FAILURE);
    }

    info->num_collectibles = 0; // Inicializar el conteo de coleccionables a 0

    for (int i = 0; i < info->height; i++)
    {
        info->map[i] = malloc(info->width + 1);
        if (!info->map[i])
        {
            fprintf(stderr, "Error: No se pudo asignar memoria para la fila %d del mapa\n", i);
            fclose(file);
            return (EXIT_FAILURE);
        }
        fgets(info->map[i], info->width + 1, file);
        fgetc(file); // Leer el salto de línea

        // Contar los coleccionables y almacenar las coordenadas de la salida en la fila actual
        for (int j = 0; j < info->width; j++)
        {
            if (info->map[i][j] == 'C')
            {
                info->num_collectibles++;
            }
            else if (info->map[i][j] == 'E')
            {
                info->exit_x = j;
                info->exit_y = i;
            }
        }
    }

    fclose(file);
    return (EXIT_SUCCESS);
}