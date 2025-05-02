/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/02 18:49:27 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw(t_game *game);

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
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
			draw_square(game, x * game->map_s, y * game->map_s, tile ? 0xFFFFFF : 0x000000, game->map_s);
		}
	}
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

	r = -1;
	ra = game->pa;
	while (++r < 1)
	{
		dof = 0;
		aTan = -1 /  tan(ra);
		if (ra > PI)
		{
			ry = ((int)game->py >> 6) -0.0001;
			rx = (game->py - ry) * aTan + game->px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = ((int)game->py << 6) + 64;
			rx = (game->py - ry) * aTan + game->px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = game->px;
			ry = game->py;
			dof = 8;
		}
		rx = game->px;
		ry = game->py;
		xo = 64;
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * game->map_x + mx;
		(void)xo;
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * game->map_x + mx;
			if (mp < game->map_x && map[mp] == 1)
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
			draw_line(game, game->px, game->py, rx, ry, 0x000000);
		}
	}
}

void	display_direction(t_game *game)
{
	int	line_length = 30;
	int	end_x = game->player_pos_x + cos(game->pa) * line_length;
	int	end_y = game->player_pos_y + sin(game->pa) * line_length;
	draw_line(game, game->player_pos_x, game->player_pos_y, end_x, end_y, 0x00FF00);
}


void    display_player(t_game *game)
{
	
	if (!game->mlx)
		printf("KO conexão\n");
	if (!game->mlx_window)
		printf("KO janela\n");
	if (!game->player_pos_x)
		printf("KO x\n");
	if (!game->player_pos_y)
		printf("KO y\n");
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x, game->player_pos_y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 1, game->player_pos_y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x, game->player_pos_y + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 1, game->player_pos_y + 1, 0xFF0000);
	
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 2, game->player_pos_y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 2, game->player_pos_y + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x, game->player_pos_y + 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 1, game->player_pos_y + 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->mlx_window, game->player_pos_x + 2, game->player_pos_y + 2, 0xFF0000);
}

int		key_press_handler(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 'W')
	{
		game->px -= game->pdx;
		game->py -= game->py;
		if (game->player_pos_y > 0)
			game->player_pos_y -= SPEED;
	}
	else if (keycode == 'd' || keycode == 'D')
	{
		//game->pa -= 0.1;
		if (game->pa > 2 * PI)
			game->pa += 2 * PI;
		game->pdx = cos(game->pa) * SPEED;
		game->pdy = sin(game->pa) * SPEED;
		if (game->player_pos_x < game->screenWidth)
			game->player_pos_x += SPEED;
	}
	else if (keycode == 's' || keycode == 'S')
	{
		game->px += game->pdx;
		game->py += game->py;
		if (game->player_pos_y < game->screenHeight)
			game->player_pos_y += SPEED;
	}
	else if (keycode == 'a' || keycode == 'A')
	{
		//game->pa -= 0.1;
		if (game->pa < 0)
			game->pa += 2 * PI;
		game->pdx = cos(game->pa) * SPEED;
		game->pdy = sin(game->pa) * SPEED;
		if (game->player_pos_x > 0)
			game->player_pos_x -= SPEED;
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
	//mlx_clear_window(game->mlx, game->mlx_window);
	display_map(game);
	display_player(game);
	display_view(game);
	display_direction(game);
}

void    init_window(t_game *game)
{
	game->player_pos_x = 200;
	game->player_pos_y = 200;
	game->screenWidth = 0;
	game->screenHeight = 0;
	mlx_get_screen_size(game->mlx, &game->screenWidth, &game->screenHeight);
	printf("Screen size %dWx%dH\n", game->screenWidth, game->screenHeight);
	game->screenWidth /= 2;
	game->screenHeight /= 2;
	game->mlx_window = mlx_new_window(game->mlx, game->screenWidth, game->screenHeight, "cub3d");
	game->pa = 0;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	draw(game);
	mlx_hook(game->mlx_window, 2, 1L << 0, key_press_handler, game);
	mlx_loop(game->mlx);
}
