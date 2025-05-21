/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:56:03 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/13 16:25:21 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	a_press_handler(t_game *game)
{
	float	side_dx;
	float	side_dy;

	side_dx = cos(game->pa - PI / 2) * SPEED;
	side_dy = sin(game->pa - PI / 2) * SPEED;
	if (game->px > 0 && game->py > 0)
	{
		game->px += side_dx;
		game->py += side_dy;
	}
}

void	d_press_handler(t_game *game)
{
	float	side_dx;
	float	side_dy;

	side_dx = cos(game->pa + PI / 2) * SPEED;
	side_dy = sin(game->pa + PI / 2) * SPEED;
	if (game->px < game->screen_width && game->py < game->screen_height)
	{
		game->px += side_dx;
		game->py += side_dy;
	}
}

void	w_press_handler(t_game *game)
{
	if (game->py > 0)
	{
		game->px -= -game->pdx;
		game->py -= -game->pdy;
	}
}

void	s_press_handler(t_game *game)
{
	if (game->py < game->screen_height)
	{
		game->px += -game->pdx;
		game->py += -game->pdy;
	}
}
