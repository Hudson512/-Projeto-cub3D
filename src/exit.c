/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:31:50 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/03 09:15:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_mem(get_mem_address());
	exit(1);
}

void	sucess_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_mem(get_mem_address());
	exit(0);
}

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_mem(get_mem_address());
	exit(1);
}

int	close_window_x(t_game *game)
{
	if (game && game->mlx && game->mlx_w)
	{
		mlx_destroy_image(game->mlx, game->screen_image.img_ptr);
		mlx_destroy_image(game->mlx, game->textures.north.img);
		mlx_destroy_image(game->mlx, game->textures.south.img);
		mlx_destroy_image(game->mlx, game->textures.east.img);
		mlx_destroy_image(game->mlx, game->textures.west.img);
		mlx_destroy_window(game->mlx, game->mlx_w);
		mlx_destroy_display(game->mlx);
	}
	sucess_exit("Janela fechada!\n");
	return (0);
}
