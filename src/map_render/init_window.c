/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/05 10:11:41 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw(t_game *game);

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_window, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
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

void draw_square(t_game *game, int x, int y, int color, int map_s)
{
	for (int i = 0; i < map_s - 1; i++)
		for (int j = 0; j < map_s - 1; j++)
			mlx_pixel_put(game->mlx, game->mlx_window, x + i, y + j, color);
}

void	display_map(t_game *game)
{
	char map[] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	game->map_x = 8;
	game->map_y = 8;
	game->map_s = 64;
	for (int y = 0; y < game->map_y; y++)
	{
		for (int x = 0; x < game->map_x; x++) {
			int tile = map[y * game->map_x + x];
			draw_square(game, x * game->map_s, y * game->map_s, tile ? 0xFFFFFF : 0x202020, game->map_s);
		}
	}
}

float distance(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	display_view(t_game *game)
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
	float	nTan;
	float	disH;
	float	hx;
	float	hy;
	float	disV;
	float	vx;
	float	vy;
	int map[] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	r = -1;
	ra = game->pa - DR * 30;
	yo = 64;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	while (++r < 60)
	{
		// Horizontal
		dof = 0;
		aTan = -1/tan(ra);
		rx = game->px;
		ry = game->py;
		xo = 64;
		disH = 1000000;
		hx = game->px;
		hy = game->py;
		if (ra > PI)
		{
			ry = (((int)game->py >> 6) << 6) - 0.0001;
			rx = (game->py - ry) * aTan + game->px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)game->py >> 6) << 6) + 64;
			rx = (game->py - ry) * aTan + game->px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = game->px;
			ry = game->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * game->map_x + mx;
			if (mp > 0 && mp < game->map_x * game->map_y && map[mp] == 1)
			{
				dof = 8;
				hx = rx;
				hy = ry;
				disH = distance(game->px, game->py, hx, hy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		//draw_line(game, game->px, game->py, rx, ry, 0xFF0000);

		// Vertical
		dof = 0;
		nTan = -tan(ra);
		disV = 1000000;
		vx = game->px;
		vy = game->py;
		if (ra > PI2 && ra < PI3)
		{
			rx = (((int)game->px >> 6) << 6) - 0.0001;
			ry = (game->px - rx) * nTan + game->py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < PI2 || ra > PI3)
		{
			rx = (((int)game->px >> 6) << 6) + 64;
			ry = (game->px - rx) * nTan + game->py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = game->px;
			ry = game->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * game->map_x + mx;
			if (mp > 0 && mp < game->map_x * game->map_y && map[mp] == 1)
			{
				dof = 8;
				vx = rx;
				vy = ry;
				disV = distance(game->px, game->py, vx, vy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
		}
		else
		{
			rx = hx;
			ry = hy;
		}
		draw_line(game, game->px, game->py, rx, ry, 0xFF0000);
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	display_direction(t_game *game)
{
	int	line_length = 30;
	int	end_x = game->px + cos(game->pa) * line_length;
	int	end_y = game->py + sin(game->pa) * line_length;
	draw_line(game, game->px, game->py, end_x, end_y, 0x00FF00);
}


void    display_player(t_game *game)
{
	
	if (!game->mlx)
		printf("KO conexão\n");
	if (!game->mlx_window)
		printf("KO janela\n");
	if (!game->px)
		printf("KO x\n");
	if (!game->py)
		printf("KO y\n");
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px, game->py + 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 1, game->py + 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->px + 2, game->py + 2, 0xFF0000);
}

int		key_press_handler(int keycode, t_game *game)
{
	if (keycode == 'a' || keycode == 'A')
	{
		//game->pa -= 0.1;
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
	else if (keycode == 'd' || keycode == 'D')
	{
		//game->pa -= 0.1;
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
	else if (keycode == 'w' || keycode == 'W')
	{
		game->px += game->pdx;
		game->py += game->pdy;
		if (game->py > 0)
		{
			game->py -= SPEED;
			game->py -= SPEED;
		}
	}
	else if (keycode == 's' || keycode == 'S')
	{
		game->px -= game->pdx;
		game->py -= game->pdy;
		if (game->py < game->screen_height)
		{
			game->py += SPEED;
			game->py += SPEED;
		}
	}
	else if (keycode == 65361)
	{
		
		game->pa -= 0.1;
		if (game->pa < 0)
			game->pa += 2 * PI;
		game->pdx = cos(game->pa) * SPEED;
		game->pdy = sin(game->pa) * SPEED;
	}
	else if (keycode == 65363)
	{
		
		game->pa += 0.1;
		if (game->pa > 2 * PI)
			game->pa -= 2 * PI;
		game->pdx = cos(game->pa) * SPEED;
		game->pdy = sin(game->pa) * SPEED;
	}
	return (draw(game), 0);
}

void	draw(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_window);
	display_map(game);
	display_player(game);
	display_view(game);
	display_direction(game);
}

void    init_window(t_game *game)
{
	game->px = 300;
	game->py = 300;
	game->screen_width = 0;
	game->screen_height = 0;
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	printf("Screen size %dWx%dH\n", game->screen_width, game->screen_height);
	game->screen_width /= 2;
	game->screen_height /= 2;
	game->mlx_window = mlx_new_window(game->mlx, game->screen_width, game->screen_height, "cub3d");
	game->pa = 0;
	game->px = 300;
	game->py = 300;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	draw(game);
	mlx_hook(game->mlx_window, 2, 1L << 0, key_press_handler, game);
	mlx_loop(game->mlx);
}
