/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evennts_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:38:53 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/27 14:19:56 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window_x(t_game *game)
{
	if (game && game->mlx && game->mlx_w)
	{
		mlx_destroy_image(game->mlx, game->screen_image.img_ptr);
		mlx_destroy_window(game->mlx, game->mlx_w);
		mlx_destroy_display(game->mlx);
	}
	sucess_exit("Janela fechada!\n");
	exit(0);
}

void	handle_zoom_out(t_game *game)
{
	int		can_zoom;
	double	next_plane_x;
	double	next_plane_y;

	next_plane_x = game->plane_x * (1.0 + ZOOM_FACTOR);
	next_plane_y = game->plane_y * (1.0 + ZOOM_FACTOR);
	can_zoom = 1;
	if (fabs(game->plane_x) > 1e-6
		&& fabs(next_plane_x) > MAX_PLANE_ACTIVE_COMPONENT)
		can_zoom = 0;
	if (fabs(game->plane_y) > 1e-6
		&& fabs(next_plane_y) > MAX_PLANE_ACTIVE_COMPONENT)
		can_zoom = 0;
	if (can_zoom)
	{
		game->plane_x = next_plane_x;
		game->plane_y = next_plane_y;
		game->fov_scale_factor /= (1.0 + ZOOM_FACTOR);
	}
}

void	handle_zoom_in(t_game *game)
{
	int		can_zoom;
	double	next_plane_x;
	double	next_plane_y;

	can_zoom = 1;
	next_plane_x = game->plane_x * (1.0 - ZOOM_FACTOR);
	next_plane_y = game->plane_y * (1.0 - ZOOM_FACTOR);
	if (fabs(game->plane_x) > 1e-6
		&& fabs(next_plane_x) < MIN_PLANE_ACTIVE_COMPONENT)
		can_zoom = 0;
	if (fabs(game->plane_y) > 1e-6
		&& fabs(next_plane_y) < MIN_PLANE_ACTIVE_COMPONENT)
		can_zoom = 0;
	if (fabs(game->plane_x) < MIN_PLANE_ACTIVE_COMPONENT
		&& fabs(game->plane_y) < MIN_PLANE_ACTIVE_COMPONENT)
		can_zoom = 0;
	if (can_zoom)
	{
		game->plane_x = next_plane_x;
		game->plane_y = next_plane_y;
		game->fov_scale_factor /= (1.0 - ZOOM_FACTOR);
	}
}

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
