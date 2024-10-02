/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:03:42 by mcentell          #+#    #+#             */
/*   Updated: 2024/10/02 21:22:12 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/get_next_line.h"
#include "re_so_long.h"

void process_keypress(int keycode, int *new_x, int *new_y);

void init_info_map(t_info_map *info)
{
    info->width = 0;
    info->height = 0;
    info->map = NULL;
    info->player_x = 0;
    info->player_y = 0;
    info->num_collectibles = 0;
    info->exit_x = 0;
    info->exit_y = 0;
    info->exit_open = 0; // Inicializar exit_open a 0 (cerrado)
}

int close_window(t_game *game) 
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

void draw_map(t_game *game)
{
    int x, y;

    for (y = 0; y < game->info.height; y++)
    {
        for (x = 0; x < game->info.width; x++)
        {
            printf("Dibujando tile en (%d, %d): %c\n", x, y, game->info.map[y][x]);
            if (game->info.map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->info.map[y][x] == 'P')
            {
                if (game->img_player == NULL)
                {
                    fprintf(stderr, "Error: Imagen del jugador es nula\n");
                    exit(EXIT_FAILURE);
                }
                printf("Dibujando jugador\n");
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            }
            else if (game->info.map[y][x] == 'C')
            {
                if (game->img_collectible == NULL)
                {
                    fprintf(stderr, "Error: Imagen del coleccionable es nula\n");
                    exit(EXIT_FAILURE);
                }
                printf("Dibujando coleccionable\n");
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
            }
            else
                mlx_put_image_to_window(game->mlx, game->win, game->img_empty, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

void draw_tile(t_game *game, int x, int y, char tile)
{
    void *img;

    if (tile == '0')
        img = game->img_empty;
    else if (tile == 'P')
        img = game->img_player;
    else if (tile == '1')
        img = game->img_wall;
    else if (tile == 'C')
        img = game->img_collectible;
    else if (tile == 'E')
        img = game->img_exit;
    else
        img = game->img_empty;

    // Verifica que la imagen no sea nula antes de dibujarla
    if (img)
    {
        mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
    }
    else
    {
        fprintf(stderr, "Error: Imagen nula en draw_tile\n");
    }
}

int handle_keypress(int keycode, t_game *game)
{
    int new_x = game->info.player_x;
    int new_y = game->info.player_y;

    if (keycode == 65307) // Escape key
    {
        close_window(game);
        return (0);
    }

    process_keypress(keycode, &new_x, &new_y);

    if (new_y >= 0 && new_y < game->info.height && new_x >= 0 && new_x < game->info.width && game->info.map[new_y][new_x] != '1')
    {
        move_player(game, new_x, new_y);
    }
    else
    {
        printf("Movimiento fuera de los límites o en una pared: new_x = %d, new_y = %d\n", new_x, new_y);
    }

    return (0);
}

void update_player_position(t_game *game, int new_x, int new_y)
{
    // Redibujar la casilla anterior como vacía
    draw_tile(game, game->info.player_x, game->info.player_y, '0');

    // Actualizar el mapa
    game->info.map[game->info.player_y][game->info.player_x] = '0';
    game->info.map[new_y][new_x] = 'P';
    game->info.player_x = new_x;
    game->info.player_y = new_y;

    // Redibujar la nueva posición del jugador
    draw_tile(game, new_x, new_y, 'P');
}

void handle_collectible(t_game *game, int new_x, int new_y)
{
    if (game->info.map[new_y][new_x] == 'C')
    {
        game->info.num_collectibles--;
        printf("Coleccionables restantes: %d\n", game->info.num_collectibles);

        if (game->info.num_collectibles == 0)
        {
            printf("Todos los coleccionables recogidos! Ahora puedes salir.\n");
            game->info.exit_open = 1; // Cambiar a 1 (abierto)
            draw_tile(game, game->info.exit_x, game->info.exit_y, 'E');
        }
    }
}

void handle_exit(t_game *game, int new_x, int new_y)
{
    if (game->info.map[new_y][new_x] == 'E' && game->info.exit_open)
    {
        printf("Felicidades! Has completado el nivel.\n");
        exit(0); // Terminar el juego con éxito
    }
}

void move_player(t_game *game, int new_x, int new_y)
{
    static int move_count = 0; // Contador de movimientos

    move_count++;
    printf("Número de movimientos: %d\n", move_count);

    handle_collectible(game, new_x, new_y);
    handle_exit(game, new_x, new_y);
    update_player_position(game, new_x, new_y);
}

void process_keypress(int keycode, int *new_x, int *new_y)
{
    if (keycode == 119) // W key
        (*new_y)--;
    else if (keycode == 115) // S key
        (*new_y)++;
    else if (keycode == 97) // A key
        (*new_x)--;
    else if (keycode == 100) // D key
        (*new_x)++;
}

void set_initial_player_position(t_info_map *info)
{
    int y = 0;
    while (y < info->height)
    {
        int x = 0;
        while (x < info->width)
        {
            if (info->map[y][x] == 'P')
            {
                info->player_x = x;
                info->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}

void init_game(t_info_map *info) {
    init_info_map(info);
}

void load_map(const char *filename, t_info_map *info) {
    if (get_map_dimensions(filename, info) == EXIT_FAILURE) {
        fprintf(stderr, "Error getting map dimensions\n");
        exit(EXIT_FAILURE);
    }

    if (read_map(filename, info) == EXIT_FAILURE) {
        fprintf(stderr, "Error reading map\n");
        free_info_map(info);
        exit(EXIT_FAILURE);
    }
}

void validate_map_and_set_position(t_info_map *info) {
    if (validate_map(info) == EXIT_FAILURE) {
        free_info_map(info);
        exit(EXIT_FAILURE);
    }

    set_initial_player_position(info);
}

void init_mlx(t_game *game) {
    game->mlx = mlx_init();
    if (game->mlx == NULL) {
        fprintf(stderr, "Error initializing MLX\n");
        free_info_map(&game->info);
        exit(EXIT_FAILURE);
    }

    game->win = mlx_new_window(game->mlx, game->info.width * TILE_SIZE, game->info.height * TILE_SIZE, "so_long");
    if (game->win == NULL) {
        fprintf(stderr, "Error creating window\n");
        free(game->mlx);
        free_info_map(&game->info);
        exit(EXIT_FAILURE);
    }
}

void setup_events(t_game *game) {
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_key_hook(game->win, handle_keypress, game);
}

void start_game_loop(t_game *game) {
    mlx_loop(game->mlx);
}

int main(int argc, char **argv) {
    t_info_map info;
    t_game game;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    init_game(&info);
    load_map(argv[1], &info);
    validate_map_and_set_position(&info);

    game.info = info;

    init_mlx(&game);
    load_images(&game);
    draw_map(&game);
    setup_events(&game);
    start_game_loop(&game);

    free_info_map(&info);
    return (EXIT_SUCCESS);
}