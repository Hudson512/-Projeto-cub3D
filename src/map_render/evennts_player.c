/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evennts_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:38:53 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/03 09:13:05 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_movement_keys(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		player_move(game, game->dir_x * game->move_speed,
			game->dir_y * game->move_speed);
	else if (keycode == KEY_S)
		player_move(game, -game->dir_x * game->move_speed,
			-game->dir_y * game->move_speed);
	else if (keycode == KEY_A)
		player_move(game, -game->plane_x * game->move_speed,
			-game->plane_y * game->move_speed);
	else if (keycode == KEY_D)
		player_move(game, game->plane_x * game->move_speed,
			game->plane_y * game->move_speed);
	else if (keycode == KEY_LEFT_ARROW)
		player_rotate(game, -game->rot_speed);
	else if (keycode == KEY_RIGHT_ARROW)
		player_rotate(game, game->rot_speed);
	else
		return (0);
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (!game)
		return (1);
	if (keycode == KEY_ESC)
		close_window_x(game);
	else if (handle_movement_keys(keycode, game))
		;
	else if (keycode == KEY_PLUS)
		handle_zoom_in(game);
	else if (keycode == KEY_MINUS)
		handle_zoom_out(game);
	else
		return (0);
	return (render_next_frame(game), 0);
}
