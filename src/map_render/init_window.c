/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/09 14:56:57 by lantonio         ###   ########.fr       */
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

void	draw_map(t_game *game, int *map)
{
	int	y;
	int	x;
	int	tile;
	int	color;

	game->map_x = 8;
	game->map_y = 8;
	game->map_s = 64;
	y = -1;
	while (++y < game->map_y)
	{
		x = -1;
		while (++x < game->map_x)
		{
			tile = map[y * game->map_x + x];
			color = 0x202020;
			if (tile)
				color = 0xFFFFFF;
			if (DEBUG)
				draw_square(game, x * game->map_s, y * game->map_s, color);
		}
	}
	(void)color;
}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_3d(t_game *game, t_render render)
{
	int	i;
	int	j;
	int	pos_x;

	i = -1;
	pos_x = DEBUG ? (game->screen_width / 2) + 32 : 0;
	while (++i < render.lineH)
	{
		j = -1;
		while (++j < RAY_WIDTH)
			mlx_pixel_put(game->mlx, game->mlx_w,
				pos_x + render.r * RAY_WIDTH + j,
				render.lineO + i, render.color);
	}
}

void	draw_3d_view(t_game *game, int *map)
{
	t_render	render;

	render.r = -1;
	render.ra = game->pa - DR * 30;
	render.yo = 64;
	if (render.ra < 0)
		render.ra += 2 * PI;
	if (render.ra > 2 * PI)
		render.ra -= 2 * PI;
	while (++render.r < game->player_fov)
	{
		// Horizontal
		render.dof = 0;
		render.aTan = -1 / tan(render.ra);
		render.rx = game->px;
		render.ry = game->py;
		render.xo = 64;
		render.disH = 1000000;
		render.hx = game->px;
		render.hy = game->py;
		if (render.ra > PI)
		{
			render.ry = (((int)game->py >> 6) << 6) - 0.0001;
			render.rx = (game->py - render.ry) * render.aTan + game->px;
			render.yo = -64;
			render.xo = -render.yo * render.aTan;
		}
		if (render.ra < PI)
		{
			render.ry = (((int)game->py >> 6) << 6) + 64;
			render.rx = (game->py - render.ry) * render.aTan + game->px;
			render.yo = 64;
			render.xo = -render.yo * render.aTan;
		}
		if (render.ra == 0 || render.ra == PI)
		{
			render.rx = game->px;
			render.ry = game->py;
			render.dof = 8;
		}
		while (render.dof < 8)
		{
			render.mx = (int)(render.rx) >> 6;
			render.my = (int)(render.ry) >> 6;
			render.mp = render.my * game->map_x + render.mx;
			if (render.mp > 0 && render.mp < game->map_x * game->map_y
				&& map[render.mp] > 0)
			{
				render.dof = 8;
				render.hx = render.rx;
				render.hy = render.ry;
				render.disH = distance(game->px, game->py,
						render.hx, render.hy);
			}
			else
			{
				render.rx += render.xo;
				render.ry += render.yo;
				render.dof += 1;
			}
		}
		//draw_line(game, game->px, game->py, render.rx, render.ry, 0xFF0000);
		render.dof = 0; // Vertical
		render.nTan = -tan(render.ra);
		render.disV = 1000000;
		render.vx = game->px;
		render.vy = game->py;
		if (render.ra > PI2 && render.ra < PI3)
		{
			render.rx = (((int)game->px >> 6) << 6) - 0.0001;
			render.ry = (game->px - render.rx) * render.nTan + game->py;
			render.xo = -64;
			render.yo = -render.xo * render.nTan;
		}
		if (render.ra < PI2 || render.ra > PI3)
		{
			render.rx = (((int)game->px >> 6) << 6) + 64;
			render.ry = (game->px - render.rx) * render.nTan + game->py;
			render.xo = 64;
			render.yo = -render.xo * render.nTan;
		}
		if (render.ra == 0 || render.ra == PI)
		{
			render.rx = game->px;
			render.ry = game->py;
			render.dof = 8;
		}
		while (render.dof < 8)
		{
			render.mx = (int)(render.rx) >> 6;
			render.my = (int)(render.ry) >> 6;
			render.mp = render.my * game->map_x + render.mx;
			if (render.mp > 0 && render.mp < game->map_x * game->map_y
				&& map[render.mp] > 0)
			{
				render.dof = 8;
				render.vx = render.rx;
				render.vy = render.ry;
				render.disV = distance(game->px, game->py, render.vx,
						render.vy);
			}
			else
			{
				render.rx += render.xo;
				render.ry += render.yo;
				render.dof += 1;
			}
		}
		render.rx = render.hx;
		render.ry = render.hy;
		render.disT = render.disH;
		render.color = 0xFF0000;
		if (render.disV < render.disH)
		{
			render.rx = render.vx;
			render.ry = render.vy;
			render.disT = render.disV;
			render.color = 0xCC0000;
		}
		if (DEBUG)
			draw_line(game, game->px, game->py, render.rx, render.ry, 0xFF0000);
		game->ca = game->pa - render.ra; //3D 
		if (game->ca < 0)
			game->ca += 2 * PI;
		if (game->ca > 2 * PI)
			game->ca -= 2 * PI;
		render.disT = render.disT * cos(game->ca);
		render.lineH = (game->map_s * 320) / render.disT;
		if (render.lineH > 320)
			render.lineH = 320;
		render.lineO = 160 - render.lineH / 2;
		draw_3d(game, render);
		render.ra += DR;
		if (render.ra < 0)
			render.ra += 2 * PI;
		if (render.ra > 2 * PI)
			render.ra -= 2 * PI;
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

void	draw(t_game *game)
{
	int	map[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

	if (CLEAR)
		mlx_clear_window(game->mlx, game->mlx_w);
	draw_map(game, map);
	draw_player(game);
	draw_pfov(game);
	draw_3d_view(game, map);
}

void	init_window(t_game *game)
{
	game->px = 300;
	game->py = 300;
	game->screen_width = 0;
	game->screen_height = 0;
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	printf("Screen size: %dWx%dH\n", game->screen_width, game->screen_height);
	game->screen_width /= 2;
	game->screen_height /= 2;
	game->mlx_w = mlx_new_window(game->mlx,
			game->screen_width, game->screen_height, "cub3d");
	game->pa = 0;
	game->px = 300;
	game->py = 300;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	game->player_fov = 64;
	draw(game);
	mlx_hook(game->mlx_w, 2, 1L << 0, key_press_handler, game);
	mlx_loop(game->mlx);
}
