/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:26 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/14 12:48:37 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_s)
	{
		j = -1;
		while (++j < game->map_s)
			mlx_pixel_put(game->mlx, game->mlx_w, x + i, y + j, color);
	}
}

static int	is_valid_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;
	int	tile;
	int	color;

	y = -1;
	while (++y < game->map_y)
	{
		x = -1;
		while (++x < game->map_x)
		{
			tile = game->config.new_map[y][x];
			color = 0x202020;
			if (tile - 48)
				color = 0xFFFFFF;
			if (is_valid_player(game->config.new_map[y][x]))
				color = 0x202020;
			if (DEBUG)
				draw_square(game, x * game->map_s, y * game->map_s, color);
		}
	}
}

void	draw_3d(t_game *game, t_render render)
{
	int	i;
	int	j;
	int	pos_x;

	i = -1;
	pos_x = 0;
	if (DEBUG)
		pos_x = (game->screen_width / 2);
	while (++i < render.lineH)
	{
		j = -1;
		while (++j < RAY_WIDTH)
			mlx_pixel_put(game->mlx, game->mlx_w,
				pos_x + render.r * RAY_WIDTH + j,
				render.lineO + i, render.color);
	}
}

void	draw_pfov(t_game *game)
{
	int	line_length;
	int	end_x;
	int	end_y;

	line_length = 30;
	end_x = game->px + cos(game->pa) * line_length;
	end_y = game->py + sin(game->pa) * line_length;
	if (DEBUG)
		draw_line(game, game->px, game->py, end_x, end_y, 0x00FF00);
}

void	draw_player(t_game *game)
{
	int	cor;

	if (!game->px)
		printf("KO x\n");
	if (!game->py)
		printf("KO y\n");
	cor = 0xFF0000;
	if (DEBUG)
	{
		mlx_pixel_put(game->mlx, game->mlx_w, game->px, game->py, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 1, game->py, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px, game->py + 1, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 1, game->py + 1, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 2, game->py, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 2, game->py + 1, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px, game->py + 2, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 1, game->py + 2, cor);
		mlx_pixel_put(game->mlx, game->mlx_w, game->px + 2, game->py + 2, cor);
	}
}
