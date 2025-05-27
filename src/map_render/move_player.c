/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:40:05 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/27 14:40:01 by lantonio         ###   ########.fr       */
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

void	player_move(t_game *game, double move_x_component, double move_y_component)
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
		&& game->config.map[map_check_y] != NULL
		&& map_check_x >= 0 && map_check_x < (int)ft_strlen(game->config.map[map_check_y])
		&& game->config.map[map_check_y][map_check_x] != '1')
	{
		game->config.player_x = new_player_x;
		game->config.player_y = new_player_y;
	}
}

void	player_zoom(t_game *game, double angle)
{
	if (!game)
		return ;
	game->move_speed += angle * 0.01; // Ajuste a sensibilidade do zoom
	if (game->move_speed < 0.01) // Limite mínimo de velocidade
		game->move_speed = 0.01;
	else if (game->move_speed > 0.5) // Limite máximo de velocidade
		game->move_speed = 0.5;
}
