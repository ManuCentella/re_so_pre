/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/07 17:09:59 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

// Implementación de free_info_map
void free_info_map(t_info_map *info) {
    for (int i = 0; i < info->height; i++) {
        free(info->map[i]);
    }
    free(info->map);
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


int read_map(const char *filename, t_info_map *info) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        return (EXIT_FAILURE);
    }

    info->map = malloc(info->height * sizeof(char *));
    if (!info->map) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el mapa\n");
        close(fd);
        return (EXIT_FAILURE);
    }

    info->num_collectibles = 0; // Inicializar el conteo de coleccionables a 0

    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL && i < info->height) {
        int line_length = ft_strlen(line);
        if (line[line_length - 1] == '\n')
            line[line_length - 1] = '\0';

        if (ft_strlen(line) != (size_t)info->width) { // Convertir info->width a size_t
            fprintf(stderr, "Error: El mapa no es rectangular\n");
            free(line);
            free_info_map(info);
            close(fd);
            return (EXIT_FAILURE);
        }

        info->map[i] = line;

        // Contar los coleccionables y almacenar las coordenadas de la salida en la fila actual
        int j = 0;
        while (j < info->width) {
            if (info->map[i][j] == 'C') {
                info->num_collectibles++;
            } else if (info->map[i][j] == 'E') {
                info->exit_x = j;
                info->exit_y = i;
            } else if (info->map[i][j] == 'P') {
                info->player_x = j;
                info->player_y = i;
            }
            j++;
        }
        i++;
    }

    close(fd);
    return (EXIT_SUCCESS);
}