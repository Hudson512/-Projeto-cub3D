/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_placement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:41:02 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/28 12:41:48 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_direction_n_s(t_game *game)
{
	if (game->config.player_dir == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else if (game->config.player_dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
}

static void	set_player_direction_w_e(t_game *game)
{
	if (game->config.player_dir == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
	else if (game->config.player_dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
}

void	init_player_direction(t_game *game)
{
	if (!game)
		return ;
	game->move_speed = 0.05;
	game->rot_speed = 0.03;
	game->fov_scale_factor = 1.0;
	set_player_direction_n_s(game);
	set_player_direction_w_e(game);
}
