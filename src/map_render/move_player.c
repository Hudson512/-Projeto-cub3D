/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:40:05 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/14 12:40:28 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void move_player(t_game *game, double move_val_x, double move_val_y)
{
    double new_player_x = game->config.player_x + move_val_x;
    double new_player_y = game->config.player_y + move_val_y;

    // Verificação de colisão simples com a célula de destino
    // Certifique-se que new_player_x e new_player_y estão dentro dos limites do mapa
    if (new_player_x >= 0 && new_player_x < game->config.map_width &&
        new_player_y >= 0 && new_player_y < game->config.map_height &&
        game->config.map[(int)new_player_y][(int)new_player_x] != '1')
    {
        game->config.player_x = new_player_x;
        game->config.player_y = new_player_y;
    }
    // Opcional: pode-se tentar mover apenas em X se Y colide, ou vice-versa, para "deslizar"
    // Mas para começar, uma verificação única é mais simples.
}

void rotate_player(t_game *game, double angle)
{
    double old_dir_x = game->dir_x;
    game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
    game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);

    double old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
    game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}