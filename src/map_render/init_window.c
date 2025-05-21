/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/14 15:21:10 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	distance(t_render render, t_game *game)
{
	return (sqrt((render.rx - game->px) * (render.rx - game->px)
			+ (render.ry - game->py) * (render.ry - game->py)));
}

void	draw_3d_view(t_game *game)
{
	t_render	render;

	render.r = -1;
	render.ra = game->pa - DR * 30;
	render.yo = game->map_s;
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
		render.xo = game->map_s;
		render.disH = 1000000;
		render.hx = game->px;
		render.hy = game->py;
		if (render.ra > PI)
		{
			render.ry = (((int)game->py / game->map_s) * game->map_s) - 0.0001;
			render.rx = (game->py - render.ry) * render.aTan + game->px;
			render.yo = -game->map_s;
			render.xo = -render.yo * render.aTan;
		}
		if (render.ra < PI)
		{
			render.ry = (((int)game->py / game->map_s) * game->map_s) + game->map_s;
			render.rx = (game->py - render.ry) * render.aTan + game->px;
			render.yo = game->map_s;
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
			render.mx = (int)(render.rx) / game->map_s;
			render.my = (int)(render.ry) / game->map_s;
			render.mp = render.my * game->map_x + render.mx;
			if (render.mp > 0 && render.mp < game->map_x * game->map_y
				&& game->config.map[render.my][render.mx] != '0')
			{
				render.dof = 8;
				render.hx = render.rx;
				render.hy = render.ry;
				render.disH = distance(render, game);
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
			render.rx = (((int)game->px / game->map_s) * game->map_s) - 0.0001;
			render.ry = (game->px - render.rx) * render.nTan + game->py;
			render.xo = -game->map_s;
			render.yo = -render.xo * render.nTan;
		}
		if (render.ra < PI2 || render.ra > PI3)
		{
			render.rx = (((int)game->px / game->map_s) * game->map_s) + game->map_s;
			render.ry = (game->px - render.rx) * render.nTan + game->py;
			render.xo = game->map_s;
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
			render.mx = (int)(render.rx) / game->map_s;
			render.my = (int)(render.ry) / game->map_s;
			render.mp = render.my * game->map_x + render.mx;
			if (render.mp > 0 && render.mp < game->map_x * game->map_y
				&& game->config.map[render.my][render.mx] != '0')
			{
				render.dof = 8;
				render.vx = render.rx;
				render.vy = render.ry;
				render.disV = distance(render, game);
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

void	draw(t_game *game)
{
	if (CLEAR)
		mlx_clear_window(game->mlx, game->mlx_w);
	draw_map(game);
	draw_player(game);
	draw_pfov(game);
	draw_3d_view(game);
}

void	init_window(t_game *game)
{
	int	dim[2];

	game->screen_width = 1024;
	game->screen_height = 512;
	if (AUTOWIDTH)
	{
		mlx_get_screen_size(game->mlx, &game->screen_width,
			&game->screen_height);
		game->screen_width /= 2;
		game->screen_height /= 2;
	}
	game->mlx_w = mlx_new_window(game->mlx,
			game->screen_width, game->screen_height, "cub3d");
	game->player_fov = 64;
	game->config.new_map = normalize_map(game->config.map, &dim[0], &dim[1]);
	game->map_x = ft_strlen(game->config.new_map[0]);
	game->map_y = count_lines(game->config.new_map);
	game->map_s = game->map_x * game->map_y;
	while (game->map_s * game->map_x > game->screen_width / 2 || game->map_s * game->map_y > game->screen_height)
		game->map_s--;
	game->pa = 0;
	game->px = (game->config.player_x * game->map_s) + (game->map_s / 3);
	game->py = (game->config.player_y * game->map_s) + (game->map_s / 3);
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	draw(game);
	mlx_hook(game->mlx_w, 2, 1L << 0, key_press_handler, game);
	mlx_loop(game->mlx);
}
