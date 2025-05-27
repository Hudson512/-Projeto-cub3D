/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/27 14:24:48 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player_direction(t_game *game)
{
	if (!game)
		return ;
	game->move_speed = 0.05;
	game->rot_speed = 0.03;
	game->fov_scale_factor = 1.0;
	if (game->config.player_dir == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else if (game->config.player_dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
	else if (game->config.player_dir == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
	else if (game->config.player_dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
}

void	my_mlx_pixel_put_to_image(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (!game || !game->screen_image.addr)
		return ;
	if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
		return ;
	dst = game->screen_image.addr + (y * game->screen_image.line_length + x
			* (game->screen_image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	init_new_window(t_game *game)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	game->win_width = game->config.map_width * TILE_SIZE;
	game->win_height = game->config.map_height * TILE_SIZE;
	if (game->win_width > screen_w)
		game->win_width = screen_w;
	if (game->win_height > screen_h)
		game->win_height = screen_h;
	game->mlx_w = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "Cub3D");
	if (!game->mlx_w)
		error_exit("Erro\n ao criar janela\n");
	game->screen_image.img_ptr = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	if (!game->screen_image.img_ptr)
		error_exit("Erro\n ao criar imagem\n");
	game->screen_image.addr = mlx_get_data_addr(game->screen_image.img_ptr,
			&game->screen_image.bits_per_pixel,
			&game->screen_image.line_length,
			&game->screen_image.endian);
	if (!game->screen_image.addr)
		error_exit("Erro\n ao obter endereço de dados da imagem\n");
}

void	init_window(t_game *game)
{
	init_new_window(game);
	init_player_direction(game);
	mlx_hook(game->mlx_w, 17, 0, close_window_x, game);
	mlx_hook(game->mlx_w, 2, 1L << 0, handle_keypress, game);
	render_next_frame(game);
	mlx_loop(game->mlx);
}
