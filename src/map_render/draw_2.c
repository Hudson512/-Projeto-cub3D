/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:06:14 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/09 16:22:23 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	t_draw_line	draw_line;

	draw_line.dx = abs(x1 - x0);
	draw_line.sx = -1;
	if (x0 < x1)
		draw_line.sx = 1;
	draw_line.dy = -abs(y1 - y0);
	draw_line.sy = -1;
	if (y0 < y1)
		draw_line.sy = 1;
	draw_line.err = draw_line.dx + draw_line.dy;
	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_w, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		draw_line.e2 = 2 * draw_line.err;
		if (draw_line.e2 >= draw_line.dy)
		{
			draw_line.err += draw_line.dy;
			x0 += draw_line.sx;
		}
		if (draw_line.e2 <= draw_line.dx)
		{
			draw_line.err += draw_line.dx;
			y0 += draw_line.sy;
		}
	}
}
