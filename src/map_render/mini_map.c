/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:53:37 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/24 12:56:00 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

// Novas funções estáticas para o minimapa
void draw_minimap_square(t_game *game, int top_left_x, int top_left_y, int size, int color)
{
    int i, j;

    if (!game || !game->screen_image.addr)
        return;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            // Adiciona o offset global do minimapa aqui
            my_mlx_pixel_put_to_image(game, top_left_x + j + MINIMAP_OFFSET_X, top_left_y + i + MINIMAP_OFFSET_Y, color);
        }
    }
}

void draw_minimap_background(t_game *game)
{
    int map_row, map_col;
    int screen_x, screen_y;

    if (!game || !game->config.map)
        return;

    for (map_row = 0; map_row < game->config.map_height; map_row++)
    {
        for (map_col = 0; map_col < game->config.map_width; map_col++)
        {
            screen_x = map_col * MINIMAP_SCALE;
            screen_y = map_row * MINIMAP_SCALE;

            if (game->config.map[map_row] && map_col < (int)ft_strlen(game->config.map[map_row]))
            {
                if (game->config.map[map_row][map_col] == '1')
                    draw_minimap_square(game, screen_x, screen_y, MINIMAP_SCALE, MINIMAP_WALL_COLOR);
                else if (game->config.map[map_row][map_col] == '0' ||
                         game->config.map[map_row][map_col] == 'N' ||
                         game->config.map[map_row][map_col] == 'S' ||
                         game->config.map[map_row][map_col] == 'E' ||
                         game->config.map[map_row][map_col] == 'W')
                    draw_minimap_square(game, screen_x, screen_y, MINIMAP_SCALE, MINIMAP_FLOOR_COLOR);
            }
            else // Se a célula estiver fora dos limites conhecidos ou a linha for curta, desenhe como parede
            {
                 draw_minimap_square(game, screen_x, screen_y, MINIMAP_SCALE, MINIMAP_WALL_COLOR);
            }
        }
    }
}

void draw_player_on_minimap(t_game *game)
{
    int player_center_x_map_pixels;
    int player_center_y_map_pixels;
    int square_top_left_x;
    int square_top_left_y;

    if (!game)
        return;

    // Posição central do jogador em pixels do minimapa (sem offset ainda)
    player_center_x_map_pixels = (int)(game->config.player_x * MINIMAP_SCALE);
    player_center_y_map_pixels = (int)(game->config.player_y * MINIMAP_SCALE);

    // Calcula o canto superior esquerdo do quadrado do jogador para centralizá-lo
    square_top_left_x = player_center_x_map_pixels - MINIMAP_PLAYER_SIZE / 2;
    square_top_left_y = player_center_y_map_pixels - MINIMAP_PLAYER_SIZE / 2;

    draw_minimap_square(game, square_top_left_x, square_top_left_y, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
}

// Função para desenhar linha (algoritmo de Bresenham)
void draw_line_on_minimap(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    if (!game)
        return;
    (void)color; // Se não for necessário usar a cor, pode ser removido
    // Adiciona o offset global do minimapa aos pontos da linha
    x0 += MINIMAP_OFFSET_X;
    y0 += MINIMAP_OFFSET_Y;
    x1 += MINIMAP_OFFSET_X;
    y1 += MINIMAP_OFFSET_Y;

    dx = abs(x1 - x0);
    sx = x0 < x1 ? 1 : -1;
    dy = -abs(y1 - y0); // Usar -abs para a forma padrão do Bresenham
    sy = y0 < y1 ? 1 : -1;
    err = dx + dy;

    while (1)
    {
        my_mlx_pixel_put_to_image(game, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) // Cuidado aqui, era "err > dy" na forma original, mas >= é comum
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) // Cuidado aqui, era "err < dx", mas <= é comum
        {
            err += dx;
            y0 += sy;
        }
    }
}
