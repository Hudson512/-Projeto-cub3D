/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:56:03 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/12 15:11:55 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	a_press_handler(t_game *game)
{
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	if (game->px > 0)
	{
		game->px -= SPEED;
		game->px -= SPEED;
	}
}

void	d_press_handler(t_game *game)
{
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
	if (game->px < game->screen_width)
	{
		game->px += SPEED;
		game->px += SPEED;
	}
}

void	w_press_handler(t_game *game)
{
	if (game->py > 0)
	{
		game->px -= -game->pdx * SPEED;
		game->py -= -game->pdy * SPEED;
	}
}

void	s_press_handler(t_game *game)
{
	if (game->py < game->screen_height)
	{
		game->px += -game->pdx * SPEED;
		game->py += -game->pdy * SPEED;
	}
}
