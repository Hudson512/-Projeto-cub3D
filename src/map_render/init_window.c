/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/06/03 09:10:41 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	game->mlx_w = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Cub3D");
	if (!game->mlx_w)
		error_exit("Erro\n ao criar janela\n");
}

static void	init_textures_n_s(t_game *game)
{
	game->textures.north.img = mlx_xpm_file_to_image(game->mlx,
			game->config.north_texture, &game->textures.north.width,
			&game->textures.north.height);
	game->textures.north.addr = mlx_get_data_addr(game->textures.north.img,
			&game->textures.north.bpp, &game->textures.north.line_length,
			&game->textures.north.endian);
	if (!game->textures.north.img || !game->textures.north.addr)
		error_exit("Erro\n ao criar imagem norte\n");
	game->textures.south.img = mlx_xpm_file_to_image(game->mlx,
			game->config.south_texture, &game->textures.south.width,
			&game->textures.south.height);
	game->textures.south.addr = mlx_get_data_addr(game->textures.south.img,
			&game->textures.south.bpp, &game->textures.south.line_length,
			&game->textures.south.endian);
	if (!game->textures.south.img || !game->textures.south.addr)
		error_exit("Erro\n ao criar imagem sul\n");
}

static void	init_textures_e_w(t_game *game)
{
	game->textures.east.img = mlx_xpm_file_to_image(game->mlx,
			game->config.east_texture, &game->textures.east.width,
			&game->textures.east.height);
	game->textures.east.addr = mlx_get_data_addr(game->textures.east.img,
			&game->textures.east.bpp, &game->textures.east.line_length,
			&game->textures.east.endian);
	if (!game->textures.east.img || !game->textures.east.addr)
		error_exit("Erro\n ao criar imagem este\n");
	game->textures.west.img = mlx_xpm_file_to_image(game->mlx,
			game->config.west_texture, &game->textures.west.width,
			&game->textures.west.height);
	game->textures.west.addr = mlx_get_data_addr(game->textures.west.img,
			&game->textures.west.bpp, &game->textures.west.line_length,
			&game->textures.west.endian);
	if (!game->textures.west.img || !game->textures.west.addr)
		error_exit("Erro\n ao criar imagem oeste\n");
}

static void	init_image(t_game *game)
{
	game->screen_image.img_ptr = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->screen_image.img_ptr)
		error_exit("Erro\n ao criar imagem\n");
	game->screen_image.addr = mlx_get_data_addr(game->screen_image.img_ptr,
			&game->screen_image.bits_per_pixel, &game->screen_image.line_length,
			&game->screen_image.endian);
	if (!game->screen_image.addr)
		error_exit("Erro\n ao obter endereço de dados da imagem\n");
	init_textures_n_s(game);
	init_textures_e_w(game);
}

void	init_window(t_game *game)
{
	if (!game || !game->mlx)
		error_exit("Erro\n ao inicializar MLX\n");
	init_new_window(game);
	init_image(game);
	init_player_direction(game);
	mlx_hook(game->mlx_w, 17, 0, close_window_x, game);
	mlx_hook(game->mlx_w, 2, 1L << 0, handle_keypress, game);
	render_next_frame(game);
	mlx_loop(game->mlx);
}
