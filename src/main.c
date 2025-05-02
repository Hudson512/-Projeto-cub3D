/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:46 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/02 11:14:33 by lantonio         ###   ########.fr       */
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
	if (parse_file(argv[1], &config))
		return (1);
	//printf("Configurações lidas:\n");
	//print_config(&config);
	game.mlx = mlx_init();
	game.config = config;
	init_window(&game);
	free_mem(get_mem_address());
	return (0);
}
