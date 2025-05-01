/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:46 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/01 15:24:34 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUso: ./cub3D mapa.cub\n", 2);
		return (1);
	}
	if (parse_file(argv[1], &config))
		return (1);
	// ler o arquivo de configuração
	printf("Configurações lidas:\n");
	print_config(&config);
	// Aqui você pode começar a inicializar o MLX e o raycasting usando config
	free_mem(get_mem_address());
	return (0);
}
