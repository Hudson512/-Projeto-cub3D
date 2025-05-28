/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:40:05 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 11:52:59 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!game)
		return ;
	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	player_move(t_game *game, double move_x_component,
		double move_y_component)
{
	double	new_player_x;
	double	new_player_y;
	int		map_check_x;
	int		map_check_y;

	if (!game || !game->config.map)
		return ;
	new_player_x = game->config.player_x + move_x_component;
	new_player_y = game->config.player_y + move_y_component;
	map_check_x = (int)new_player_x;
	map_check_y = (int)new_player_y;
	if (map_check_y >= 0 && map_check_y < game->config.map_height
		&& game->config.map[map_check_y] != NULL && map_check_x >= 0
		&& map_check_x < (int)ft_strlen(game->config.map[map_check_y])
		&& game->config.map[map_check_y][map_check_x] != '1')
	{
		game->config.player_x = new_player_x;
		game->config.player_y = new_player_y;
	}
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
