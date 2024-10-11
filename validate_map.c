/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:22:45 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/11 16:26:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

// Función para verificar si el mapa es rectangular
int is_rectangular(t_info_map *info)
{
    int y = 0;

    // Recorre cada fila del mapa y verifica que todas tengan la misma longitud
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

// Función para verificar si el mapa está rodeado de muros ('1')
int is_surrounded_by_walls(t_info_map *info)
{
    int x = 0, y = 0;

    // Verifica los bordes del mapa
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

// Función para procesar cada celda del mapa y contar los elementos importantes
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

// Función para verificar si el mapa tiene los elementos necesarios
int has_valid_elements(int player_count, int exit_count, int collectible_count)
{
    if (player_count != 1)
    {
        fprintf(stderr, "Error: El mapa debe tener exactamente una posición inicial del jugador\n");
        return (EXIT_FAILURE);
    }
    if (exit_count != 1)
    {
        fprintf(stderr, "Error: El mapa debe tener exactamente una salida\n");
        return (EXIT_FAILURE);
    }
    if (collectible_count < 1)
    {
        fprintf(stderr, "Error: El mapa debe tener al menos un coleccionable\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Función para contar los elementos del mapa
int count_map_elements(t_info_map *info, int *player_count, int *exit_count, int *collectible_count)
{
    int y = 0;
    int x;

    // Recorre cada celda del mapa y cuenta los elementos importantes
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

// Función principal para validar el mapa
int validate_map(t_info_map *info)
{
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;

    // Verificar si el mapa es rectangular
    if (is_rectangular(info) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    // Verificar si el mapa está rodeado de muros
    if (is_surrounded_by_walls(info) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    // Contar los elementos del mapa
    if (count_map_elements(info, &player_count, &exit_count, &collectible_count) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    // Verificar si el mapa tiene los elementos necesarios
    if (has_valid_elements(player_count, exit_count, collectible_count) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}