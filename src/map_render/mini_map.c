/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:53:37 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/30 20:13:51 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player_on_minimap(t_game *game)
{
	int	player_center_x_map_pixels;
	int	player_center_y_map_pixels;
	int	square_top_left[2];

	if (!game)
		return ;
	player_center_x_map_pixels = (int)(game->config.player_x * MINIMAP_SCALE);
	player_center_y_map_pixels = (int)(game->config.player_y * MINIMAP_SCALE);
	square_top_left[0] = player_center_x_map_pixels - MINIMAP_PLAYER_SIZE / 2;
	square_top_left[1] = player_center_y_map_pixels - MINIMAP_PLAYER_SIZE / 2;
	draw_minimap_square(game, square_top_left,
		MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
}

// Função para desenhar linha (algoritmo de Bresenham)
static void	keep_draw_line_on_minimap(t_game *game, int *x, int *y, t_draw draw)
{
	while (1)
	{
		my_mlx_pixel_put_to_image(game, x[0], y[0], MINIMAP_FOV_COLOR);
		if (x[0] == x[1] && y[0] == y[1])
			break ;
		draw.e2 = 2 * draw.err;
		if (draw.e2 >= draw.dy)
		{
			draw.err += draw.dy;
			x[0] += draw.sx;
		}
		if (draw.e2 <= draw.dx)
		{
			draw.err += draw.dx;
			y[0] += draw.sy;
		}
	}
}

void	draw_line_on_minimap(t_game *game, int *x, int *y)
{
	t_draw	draw;

	if (!game)
		return ;
	x[0] += MINIMAP_OFFSET_X;
	y[0] += MINIMAP_OFFSET_Y;
	x[1] += MINIMAP_OFFSET_X;
	y[1] += MINIMAP_OFFSET_Y;
	draw.dx = abs(x[1] - x[0]);
	if (x[0] < x[1])
		draw.sx = 1;
	else
		draw.sx = -1;
	draw.dy = -abs(y[1] - y[0]);
	if (y[0] < y[1])
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx + draw.dy;
	keep_draw_line_on_minimap(game, x, y, draw);
}

static void	draw_fov_ray(t_game *game, int *center, double ray_x, double ray_y)
{
	int	x[2];
	int	y[2];

	x[0] = center[0];
	y[0] = center[1];
	x[1] = center[0] + (int)(ray_x * MINIMAP_SCALE * 5);
	y[1] = center[1] + (int)(ray_y * MINIMAP_SCALE * 5);
	draw_line_on_minimap(game, x, y);
}

void	render_minimap(t_game *game)
{
	int		player_minimap[2];
	double	fov_left_x;
	double	fov_left_y;

	if (!game || !game->mlx || !game->mlx_w
		|| !game->screen_image.img_ptr || !game->screen_image.addr)
		return ;
	draw_minimap_background(game);
	draw_player_on_minimap(game);
	player_minimap[0] = (int)(game->config.player_x * MINIMAP_SCALE);
	player_minimap[1] = (int)(game->config.player_y * MINIMAP_SCALE);
	fov_left_x = game->dir_x - game->plane_x;
	fov_left_y = game->dir_y - game->plane_y;
	draw_fov_ray(game, player_minimap, fov_left_x, fov_left_y);
	draw_fov_ray(game, player_minimap, game->dir_x + game->plane_x,
		game->dir_y + game->plane_y);
}
