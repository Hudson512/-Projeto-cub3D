/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:53:37 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/27 14:37:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Novas funções estáticas para o minimapa
void	draw_minimap_square(t_game *game, int top_left_x, int top_left_y, int size, int color)
{
	int	i;
	int	j;

	if (!game || !game->screen_image.addr)
		return ;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			my_mlx_pixel_put_to_image(game, top_left_x + j + MINIMAP_OFFSET_X,
				top_left_y + i + MINIMAP_OFFSET_Y, color);
		}
	}
}

void	draw_minimap_background(t_game *game)
{
	int	map_row;
	int	map_col;
	int	screen_x;
	int	screen_y;

	if (!game || !game->config.map)
		return ;
	map_row = -1;
	while (++map_row < game->config.map_height)
	{
		map_col = -1;
		while (++map_col < game->config.map_width)
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
			else
			{
				draw_minimap_square(game, screen_x, screen_y, MINIMAP_SCALE, MINIMAP_WALL_COLOR);
			}
		}
	}
}

void	draw_player_on_minimap(t_game *game)
{
	int	player_center_x_map_pixels;
	int	player_center_y_map_pixels;
	int	square_top_left_x;
	int	square_top_left_y;

	if (!game)
		return ;
	player_center_x_map_pixels = (int)(game->config.player_x * MINIMAP_SCALE);
	player_center_y_map_pixels = (int)(game->config.player_y * MINIMAP_SCALE);
	square_top_left_x = player_center_x_map_pixels - MINIMAP_PLAYER_SIZE / 2;
	square_top_left_y = player_center_y_map_pixels - MINIMAP_PLAYER_SIZE / 2;
	draw_minimap_square(game, square_top_left_x, square_top_left_y, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
}

// Função para desenhar linha (algoritmo de Bresenham)
void	draw_line_on_minimap(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	t_draw	draw;

	if (!game)
		return ;
	x0 += MINIMAP_OFFSET_X;
	y0 += MINIMAP_OFFSET_Y;
	x1 += MINIMAP_OFFSET_X;
	y1 += MINIMAP_OFFSET_Y;
	draw.dx = abs(x1 - x0);
	draw.sx = -1;
	if (x0 < x1)
		draw.sx = 1;
	draw.dy = -abs(y1 - y0);
	draw.sy = -1;
	if (y0 < y1)
		draw.sy = 1;
	draw.err = draw.dx + draw.dy;
	while (1)
	{
		my_mlx_pixel_put_to_image(game, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		draw.e2 = 2 * draw.err;
		if (draw.e2 >= draw.dy)
		{
			draw.err += draw.dy;
			x0 += draw.sx;
		}
		if (draw.e2 <= draw.dx)
		{
			draw.err += draw.dx;
			y0 += draw.sy;
		}
	}
}

static void	draw_fov_ray(t_game *game, int center_x, int center_y,
	double ray_x, double ray_y)
{
	draw_line_on_minimap(game, center_x, center_y,
		center_x + (int)(ray_x * MINIMAP_SCALE * 5),
		center_y + (int)(ray_y * MINIMAP_SCALE * 5),
		MINIMAP_FOV_COLOR);
}

void	render_minimap(t_game *game)
{
	int		player_minimap_x;
	int		player_minimap_y;
	double	fov_left_x;
	double	fov_left_y;

	if (!game || !game->mlx || !game->mlx_w
		|| !game->screen_image.img_ptr || !game->screen_image.addr)
		return ;
	draw_minimap_background(game);
	draw_player_on_minimap(game);
	player_minimap_x = (int)(game->config.player_x * MINIMAP_SCALE);
	player_minimap_y = (int)(game->config.player_y * MINIMAP_SCALE);
	fov_left_x = game->dir_x - game->plane_x;
	fov_left_y = game->dir_y - game->plane_y;
	draw_fov_ray(game, player_minimap_x, player_minimap_y,
		fov_left_x, fov_left_y);
	draw_fov_ray(game, player_minimap_x, player_minimap_y,
		game->dir_x + game->plane_x, game->dir_y + game->plane_y);
}
