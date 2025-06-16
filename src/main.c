/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:46 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/16 09:45:00 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUso: ./cub3D mapa.cub\n", 2);
		return (1);
	}
	ft_memset(&config, 0, sizeof(t_config));
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_file(argv[1], &config))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Error\nFalha ao inicializar MLX\n");
	collect_mem(game.mlx);
	game.config = config;
	init_window(&game);
	free_mem(get_mem_address());
	return (0);
}
