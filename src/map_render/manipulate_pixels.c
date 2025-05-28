/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_pixels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:46:14 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 10:46:55 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
