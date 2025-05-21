/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evennts_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:38:53 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/21 12:53:01 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int close_window_x(t_game *game)
{
    
    if (game && game->mlx && game->mlx_w)
    {
        mlx_destroy_window(game->mlx, game->mlx_w);
    }
    sucess_exit("Janela fechada!\n");
    exit(0);
}

int handle_keypress(int keycode, t_game *game)
{
    if (!game)
        return (1);
    if (keycode == KEY_ESC)
        close_window_x(game);
    else if (keycode == KEY_W)
        player_move(game, game->dir_x * game->move_speed, game->dir_y * game->move_speed);
    else if (keycode == KEY_S)
        player_move(game, -game->dir_x * game->move_speed, -game->dir_y * game->move_speed);
    else if (keycode == KEY_A)
        player_move(game, -game->plane_x * game->move_speed, -game->plane_y * game->move_speed);
    else if (keycode == KEY_D)
        player_move(game, game->plane_x * game->move_speed, game->plane_y * game->move_speed);
    else if (keycode == KEY_LEFT_ARROW)
        player_rotate(game, -game->rot_speed);
    else if (keycode == KEY_RIGHT_ARROW)
        player_rotate(game, game->rot_speed);
    else
        return (0);
    printf("Player X: %.2f, Y: %.2f, DirX: %.2f, DirY: %.2f\n", game->config.player_x, game->config.player_y, game->dir_x, game->dir_y);
    render_next_frame(game);
    return (0);
}

