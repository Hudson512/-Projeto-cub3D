/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/06 12:39:29 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw(t_game *game);

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	sx = -1;
	if (x0 < x1)
		sx = 1;
	dy = -abs(y1 - y0);
	sy = -1;
	if (y0 < y1)
		sy = 1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_window, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_s - 1)
	{
		j = -1;
		while (++j < game->map_s - 1)
			mlx_pixel_put(game->mlx, game->mlx_window, x + i, y + j, color);
	}
}

void	display_map(t_game *game, int *map)
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
			draw_square(game, x * game->map_s, y * game->map_s, color);
		}
	}
}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_3d(t_game *game, int lineO, int lineH, int r)
{
	int	i;
	int	j;

	i = -1;
	while (++i < lineH)
	{
		j = -1;
		while (++j < game->map_s)
			mlx_pixel_put(game->mlx, game->mlx_window, (game->screen_width / 2) + r + j, lineO + i, 0xFF0000);
	}
}

void	display_view(t_game *game, int *map)
{
	t_render	render;

	render.r = -1;
	render.ra = game->pa - DR * 30;
	render.yo = 64;
	if (render.ra < 0)
		render.ra += 2 * PI;
	if (render.ra > 2 * PI)
		render.ra -= 2 * PI;
	while (++render.r < 60)
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
				&& map[render.mp] == 1)
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
				&& map[render.mp] == 1)
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
		if (render.disV < render.disH)
		{
			render.rx = render.vx;
			render.ry = render.vy;
		}
		else
		{
			render.rx = render.hx;
			render.ry = render.hy;
		}
		draw_line(game, game->px, game->py, render.rx, render.ry, 0xFF0000);
		render.lineH = (game->map_s * 320) / render.disT;//3D
		if (render.lineH > 320)
			render.lineH = 320;
		render.lineO = 160 - render.lineH / 2;
		// desenhar a linha vertical
		render.disT = render.disV;
		if (render.disH < render.disV)
			render.disT = render.disH;
		render.lineH = (game->map_s * 320) / render.disT;
		if (render.lineH > 320)
			render.lineH = 320;
		if (render.lineH < 0)
			render.lineH = 0;
		render.lineO = 160 - render.lineH / 2;
		if (render.lineO < 0)
			render.lineO = 0;
		if (render.lineO > 320)
			render.lineO = 320;
		draw_3d(game, render.lineO, render.lineH, render.r);
		render.ra += DR;
		if (render.ra < 0)
			render.ra += 2 * PI;
		if (render.ra > 2 * PI)
			render.ra -= 2 * PI;
	}
}

void	display_direction(t_game *game)
{
	int	line_length;
	int	end_x;
	int	end_y;

	line_length = 30;
	end_x = game->px + cos(game->pa) * line_length;
	end_y = game->py + sin(game->pa) * line_length;
	draw_line(game, game->px, game->py, end_x, end_y, 0x00FF00);
}

void	display_player(t_game *game)
{
	int	cor;

	if (!game->mlx)
		printf("KO conexão\n");
	if (!game->mlx_window)
		printf("KO janela\n");
	if (!game->px)
		printf("KO x\n");
	if (!game->py)
		printf("KO y\n");
	cor = 0xFF0000;
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py + 1, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py + 1, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py + 1, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py + 2, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py + 2, cor);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py + 2, cor);
}

void	a_press_handler(t_game *game)
{
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	if (game->px > 0)
	{
		game->px -= SPEED;
		game->px -= SPEED;
	}
}

void	d_press_handler(t_game *game)
{
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	if (game->px < game->screen_width)
	{
		game->px += SPEED;
		game->px += SPEED;
	}
}

void	w_press_handler(t_game *game)
{
	game->px += game->pdx;
	game->py += game->pdy;
	if (game->py > 0)
	{
		game->py -= SPEED;
		game->py -= SPEED;
	}
}

void	s_press_handler(t_game *game)
{
	game->px -= game->pdx;
	game->py -= game->pdy;
	if (game->py < game->screen_height)
	{
		game->py += SPEED;
		game->py += SPEED;
	}
}

void	right_press_handler(t_game *game)
{
	game->pa += 0.1;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
}

void	left_press_handler(t_game *game)
{
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
}

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == 'a' || keycode == 'A')
		a_press_handler(game);
	else if (keycode == 'd' || keycode == 'D')
		d_press_handler(game);
	else if (keycode == 'w' || keycode == 'W')
		w_press_handler(game);
	else if (keycode == 's' || keycode == 'S')
		s_press_handler(game);
	else if (keycode == 65361)
		left_press_handler(game);
	else if (keycode == 65363)
		right_press_handler(game);
	return (draw(game), 0);
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

	mlx_clear_window(game->mlx, game->mlx_window);
	display_map(game, map);
	display_player(game);
	display_view(game, map);
	display_direction(game);
}

void	init_window(t_game *game)
{
	game->px = 300;
	game->py = 300;
	game->screen_width = 0;
	game->screen_height = 0;
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	printf("Screen size %dWx%dH\n", game->screen_width, game->screen_height);
	game->screen_width /= 2;
	game->screen_height /= 2;
	game->mlx_window = mlx_new_window(game->mlx,
			game->screen_width, game->screen_height, "cub3d");
	game->pa = 0;
	game->px = 300;
	game->py = 300;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	draw(game);
	mlx_hook(game->mlx_window, 2, 1L << 0, key_press_handler, game);
	mlx_loop(game->mlx);
}
