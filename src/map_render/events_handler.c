/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:58:57 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/12 15:15:21 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	right_press_handler(t_game *game)
{
	game->pa += 0.1;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
}

void	left_press_handler(t_game *game)
{
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * SPEED;
	game->pdy = sin(game->pa) * SPEED;
}

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == 'a' || keycode == 'A')
		return (a_press_handler(game), draw(game), 0);
	else if (keycode == 'd' || keycode == 'D')
		return (d_press_handler(game), draw(game), 0);
	else if (keycode == 'w' || keycode == 'W')
		return (w_press_handler(game), draw(game), 0);
	else if (keycode == 's' || keycode == 'S')
		return (s_press_handler(game), draw(game), 0);
	else if (keycode == 65361)
		return (left_press_handler(game), draw(game), 0);
	else if (keycode == 65363)
		return (right_press_handler(game), draw(game), 0);
	return (0);
}
