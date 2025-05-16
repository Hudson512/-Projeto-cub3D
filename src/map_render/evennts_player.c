/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evennts_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:38:53 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/14 12:39:23 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int key_press_hook(int keycode, t_game *game)
{
    if (keycode == ESC_KEY)
        close_window_x(game);
    else if (keycode == KEY_W) // Mover para frente
        move_player(game, game->dir_x * game->move_speed, game->dir_y * game->move_speed);
    else if (keycode == KEY_S) // Mover para trás
        move_player(game, -game->dir_x * game->move_speed, -game->dir_y * game->move_speed);
    // Para movimento lateral (strafe), você usaria o vetor do plano da câmera
    else if (keycode == KEY_A) // Strafe Esquerda
        move_player(game, -game->plane_x * game->move_speed, -game->plane_y * game->move_speed);
    else if (keycode == KEY_D) // Strafe Direita
        move_player(game, game->plane_x * game->move_speed, game->plane_y * game->move_speed);
    else if (keycode == KEY_LEFT_ARROW) // Virar à Esquerda
        rotate_player(game, -game->rot_speed);
    else if (keycode == KEY_RIGHT_ARROW) // Virar à Direita
        rotate_player(game, game->rot_speed);

    // Após qualquer movimento, podemos imprimir a nova posição para depuração
    printf("Player X: %.2f, Y: %.2f, DirX: %.2f, DirY: %.2f\n",
           game->config.player_x, game->config.player_y, game->dir_x, game->dir_y);

    // IMPORTANTE: No próximo passo, chamaremos a função de renderização aqui
    // para que a tela seja atualizada após cada movimento.
    return (0);
}