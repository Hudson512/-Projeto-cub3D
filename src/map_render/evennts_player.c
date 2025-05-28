/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evennts_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:38:53 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 11:20:04 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	handle_keypress(int keycode, t_game *game)
{
	if (!game)
		return (1);
	if (keycode == KEY_ESC)
		close_window_x(game);
	else if (keycode == KEY_W)
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
	else if (keycode == KEY_PLUS)
		handle_zoom_in(game);
	else if (keycode == KEY_MINUS)
		handle_zoom_out(game);
	else
		return (0);
	return (render_next_frame(game), 0);
}
