/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:42:53 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/28 12:43:04 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_square(t_game *game, int *top_left, int size, int color)
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
			my_mlx_pixel_put_to_image(game, top_left[0] + j + MINIMAP_OFFSET_X,
				top_left[1] + i + MINIMAP_OFFSET_Y, color);
		}
	}
}

void	keep_drawing__minimap_background(t_game *game,
	int map_row, int map_col, int *screen)
{
	screen[0] = map_col * MINIMAP_SCALE;
	screen[1] = map_row * MINIMAP_SCALE;
	if (game->config.map[map_row] && map_col
		< (int)ft_strlen(game->config.map[map_row]))
	{
		if (game->config.map[map_row][map_col] == '1')
			draw_minimap_square(game, screen,
				MINIMAP_SCALE, MINIMAP_WALL_COLOR);
		else if (game->config.map[map_row][map_col] == '0' ||
				game->config.map[map_row][map_col] == 'N' ||
				game->config.map[map_row][map_col] == 'S' ||
				game->config.map[map_row][map_col] == 'E' ||
				game->config.map[map_row][map_col] == 'W')
			draw_minimap_square(game, screen,
				MINIMAP_SCALE, MINIMAP_FLOOR_COLOR);
	}
	else
	{
		draw_minimap_square(game, screen, MINIMAP_SCALE, MINIMAP_WALL_COLOR);
	}
}

void	draw_minimap_background(t_game *game)
{
	int	map_row;
	int	map_col;
	int	screen[2];

	if (!game || !game->config.map)
		return ;
	map_row = -1;
	while (++map_row < game->config.map_height)
	{
		map_col = -1;
		while (++map_col < game->config.map_width)
			keep_drawing__minimap_background(game, map_row, map_col, screen);
	}
}
