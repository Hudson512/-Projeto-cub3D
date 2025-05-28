/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/28 12:40:51 by lantonio         ###   ########.fr       */
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
