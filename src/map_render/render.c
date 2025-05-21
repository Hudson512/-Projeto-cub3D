/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:43:34 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/19 09:54:15 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// static void render_next_frame(t_game *game)
// {
//     int x; // Coluna atual da tela que estamos renderizando
    
//     if (!game || !game->mlx || !game->mlx_w || !game->screen_image.img_ptr || !game->screen_image.addr)
//         return;
    
//     if (!game->config.map || game->config.map_width <= 0 || game->config.map_height <= 0)
//         return;

//     for (x = 0; x < game->win_width; x++)
//     {
//         // 1. CALCULAR POSIÇÃO E DIREÇÃO DO RAIO
//         // camera_x: coordenada x no espaço da câmera (-1 para borda esquerda, 0 centro, 1 borda direita)
//         double camera_x = 2 * x / (double)game->win_width - 1;
//         double ray_dir_x = game->dir_x + game->plane_x * camera_x;
//         double ray_dir_y = game->dir_y + game->plane_y * camera_x;

//         // 2. POSIÇÃO INICIAL NO MAPA E DISTÂNCIAS DELTA
//         // map_x, map_y: célula atual do mapa em que o raio está
//         int map_x = (int)game->config.player_x;
//         int map_y = (int)game->config.player_y;

//         // Verificar se o jogador está dentro dos limites do mapa
//         if (map_x < 0 || map_x >= game->config.map_width || map_y < 0 || map_y >= game->config.map_height)
//         {
//             continue; // Pular para o próximo raio
//         }

//         // delta_dist_x, delta_dist_y: comprimento do raio de um lado x (ou y)
//         // para o próximo lado x (ou y). Evita divisão por zero.
//         double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x); // 1e30 é um valor muito grande
//         double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

//         // 3. DISTÂNCIAS LATERAIS INICIAIS E INCREMENTO (STEP)
//         double side_dist_x;
//         double side_dist_y;

//         int step_x;
//         int step_y;

//         int hit = 0; // Foi atingida uma parede?
//         int side;    // Lado da parede atingido? 0 para lado X (vertical), 1 para lado Y (horizontal)

//         if (ray_dir_x < 0)
//         {
//             step_x = -1;
//             side_dist_x = (game->config.player_x - map_x) * delta_dist_x;
//         }
//         else
//         {
//             step_x = 1;
//             side_dist_x = (map_x + 1.0 - game->config.player_x) * delta_dist_x;
//         }
//         if (ray_dir_y < 0)
//         {
//             step_y = -1;
//             side_dist_y = (game->config.player_y - map_y) * delta_dist_y;
//         }
//         else
//         {
//             step_y = 1;
//             side_dist_y = (map_y + 1.0 - game->config.player_y) * delta_dist_y;
//         }

//         // 4. ALGORITMO DDA
//         int max_iterations = game->config.map_width * game->config.map_height * 2; // Limite para evitar loop infinito
//         int iterations = 0;
        
//         while (hit == 0 && iterations < max_iterations)
//         {
//             iterations++;
            
//             // Pula para a próxima célula do mapa, OU na direção x OU na direção y
//             if (side_dist_x < side_dist_y)
//             {
//                 side_dist_x += delta_dist_x;
//                 map_x += step_x;
//                 side = 0; // Atingiu um lado X (parede vertical N-S)
//             }
//             else
//             {
//                 side_dist_y += delta_dist_y;
//                 map_y += step_y;
//                 side = 1; // Atingiu um lado Y (parede horizontal E-W)
//             }
//             // Verifica se o raio atingiu uma parede
//             // Certifique-se de que map_x e map_y estão dentro dos limites do mapa!
//             if (map_x >= 0 && map_x < game->config.map_width && map_y >= 0 && map_y < game->config.map_height)
//             {
//                 if (game->config.map[map_y] && map_x < (int)ft_strlen(game->config.map[map_y]) && 
//                     game->config.map[map_y][map_x] == '1')
//                     hit = 1;
//             }
//             else
//             {
//                 // Raio saiu dos limites do mapa
//                 hit = 1; // Para o loop se sair dos limites
//             }
//         }

//         // 5. CÁLCULO DA DISTÂNCIA PERPENDICULAR
//         double perp_wall_dist;
//         if (side == 0) // Atingiu um lado X
//             perp_wall_dist = (side_dist_x - delta_dist_x);
//         else // Atingiu um lado Y
//             perp_wall_dist = (side_dist_y - delta_dist_y);
        
//         // Prevenção de divisão por zero se perp_wall_dist for muito pequeno
//         if (perp_wall_dist < 0.0001) perp_wall_dist = 0.0001;

//         // 6. CÁLCULO DA ALTURA DA LINHA DA PAREDE
//         int line_height = (int)(game->win_height / perp_wall_dist);

//         // Calcular o pixel mais baixo e mais alto para preencher a faixa atual
//         int draw_start = -line_height / 2 + game->win_height / 2;
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = line_height / 2 + game->win_height / 2;
//         if (draw_end >= game->win_height)
//             draw_end = game->win_height - 1;

//         // 7. ESCOLHER COR DA PAREDE E DESENHAR
//         int color;
//         if (side == 1) // Parede horizontal (lado Y)
//         {
//             color = 0x00808080; // Cinza mais escuro (exemplo)
//         }
//         else // Parede vertical (lado X)
//         {
//             color = 0x00A9A9A9; // Cinza um pouco mais claro (exemplo)
//         }

//         // Desenhar os pixels da fatia da parede
//         for (int y = draw_start; y <= draw_end; y++)
//         {
//             my_mlx_pixel_put_to_image(game, x, y, color);
//         }

//         // DESENHAR CHÃO E TETO (CORES SÓLIDAS POR ENQUANTO)
//         // Teto: da linha 0 até draw_start
//         for (int y = 0; y < draw_start; y++)
//         {
//             my_mlx_pixel_put_to_image(game, x, y, 0x0087CEEB); // Azul céu (exemplo)
//         }
//         // Chão: de draw_end até o final da tela
//         for (int y = draw_end + 1; y < game->win_height; y++)
//         {
//             my_mlx_pixel_put_to_image(game, x, y, 0x00228B22); // Verde grama (exemplo)
//         }
//     }

//     // Após desenhar todas as colunas na imagem, coloque a imagem na janela
//     mlx_put_image_to_window(game->mlx, game->mlx_w, game->screen_image.img_ptr, 0, 0);
// }

void render_next_frame(t_game *game)
{
    
    int x; // Coluna atual da tela que estamos renderizando
    
    if (!game || !game->mlx || !game->mlx_w || !game->screen_image.img_ptr || !game->screen_image.addr)
        return;
    
    if (!game->config.map || game->config.map_width <= 0 || game->config.map_height <= 0)
        return;

    // NOTA: A ordem é importante. Se o céu/chão 3D cobrirem a tela inteira,
    // o minimapa precisa ser desenhado DEPOIS deles, ou terá seu próprio
    // fundo opaco se desenhado primeiro.
    // Para simplificar, vamos desenhar o céu/chão 3D primeiro, depois o minimapa,
    // depois as paredes 3D (o minimapa ficará por baixo das paredes 3D se houver sobreposição).
    // Uma abordagem melhor seria o minimapa ter uma área reservada e não ser sobrescrito.
    // Por enquanto, o minimapa será desenhado antes das paredes 3D,
    // e o céu/chão 3D também serão desenhados antes.

    // Preencher toda a imagem com cor de teto e chão (visão 3D)
    // (Esta é uma forma simples, poderia ser otimizada)
    for (int y_fill = 0; y_fill < game->win_height; y_fill++)
    {
        for (int x_fill = 0; x_fill < game->win_width; x_fill++)
        {
            if (y_fill < game->win_height / 2) // Metade superior é teto
                my_mlx_pixel_put_to_image(game, x_fill, y_fill, 0x0087CEEB); // Azul céu (exemplo)
            else // Metade inferior é chão
                my_mlx_pixel_put_to_image(game, x_fill, y_fill, 0x00228B22); // Verde grama (exemplo)
        }
    }
    

    // --- INÍCIO DO DESENHO DO MINIMAPA ---
    draw_minimap_background(game);
    draw_player_on_minimap(game);
    // Opcional: desenhar linhas do FOV
    // Posição central do jogador em pixels do minimapa (sem offset)
    int player_minimap_x_center = (int)(game->config.player_x * MINIMAP_SCALE);
    int player_minimap_y_center = (int)(game->config.player_y * MINIMAP_SCALE);

    // Raio esquerdo do FOV
    double fov_ray_left_x = game->dir_x - game->plane_x;
    double fov_ray_left_y = game->dir_y - game->plane_y;
    draw_line_on_minimap(game, player_minimap_x_center, player_minimap_y_center,
                         player_minimap_x_center + (int)(fov_ray_left_x * MINIMAP_SCALE * 5), // 5 é um comprimento arbitrário
                         player_minimap_y_center + (int)(fov_ray_left_y * MINIMAP_SCALE * 5),
                         MINIMAP_FOV_COLOR);
    // Raio direito do FOV
    double fov_ray_right_x = game->dir_x + game->plane_x;
    double fov_ray_right_y = game->dir_y + game->plane_y;
    draw_line_on_minimap(game, player_minimap_x_center, player_minimap_y_center,
                         player_minimap_x_center + (int)(fov_ray_right_x * MINIMAP_SCALE * 5),
                         player_minimap_y_center + (int)(fov_ray_right_y * MINIMAP_SCALE * 5),
                         MINIMAP_FOV_COLOR);
    // --- FIM DO DESENHO DO MINIMAPA (RAIOS SERÃO DESENHADOS ABAIXO) ---

    
    // Loop de Ray Casting para a visão 3D
    for (x = 0; x < game->win_width; x++)
    {
        double camera_x = 2 * x / (double)game->win_width - 1;
        double ray_dir_x = game->dir_x + game->plane_x * camera_x;
        double ray_dir_y = game->dir_y + game->plane_y * camera_x;

        int map_x = (int)game->config.player_x;
        int map_y = (int)game->config.player_y;

        if (map_x < 0 || map_x >= game->config.map_width || map_y < 0 || map_y >= game->config.map_height)
        {
            // Se o jogador estiver fora do mapa, não podemos lançar raios de forma segura
            // No entanto, a lógica de movimento deve impedir isso.
            // Se chegar aqui, é um estado inesperado.
            continue;
        }

        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side = 0; // Inicialize side

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->config.player_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->config.player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->config.player_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->config.player_y) * delta_dist_y;
        }

        int max_iterations = game->config.map_width * game->config.map_height * 2; 
        int iterations = 0;
        
       

        while (hit == 0 && iterations < max_iterations)
        {
            iterations++;
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0; 
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1; 
            }
            if (map_x >= 0 && map_x < game->config.map_width && map_y >= 0 && map_y < game->config.map_height)
            {
                if (game->config.map[map_y] && map_x < (int)ft_strlen(game->config.map[map_y]) && 
                    game->config.map[map_y][map_x] == '1')
                {
                    hit = 1;
                   
                }
            }
            else
            {
                hit = 1; 
               
            }
        }

        double perp_wall_dist;
        // Distância real ao longo do raio até o ponto de colisão.
        // Esta é uma forma mais precisa para o comprimento do raio no minimapa.
        double dist_along_ray_to_wall;

        if (side == 0)
        {
            perp_wall_dist = (side_dist_x - delta_dist_x);
            dist_along_ray_to_wall = (map_x - game->config.player_x + (1.0 - step_x) / 2.0) / ray_dir_x;

        }
        else
        {
            perp_wall_dist = (side_dist_y - delta_dist_y);
            dist_along_ray_to_wall = (map_y - game->config.player_y + (1.0 - step_y) / 2.0) / ray_dir_y;
        }
        
        if (perp_wall_dist < 0.0001) perp_wall_dist = 0.0001;
        if (dist_along_ray_to_wall < 0.0001) dist_along_ray_to_wall = 0.0001;


        // --- DESENHAR O RAIO ATUAL NO MINIMAPA ---
        // Usar dist_along_ray_to_wall para o comprimento correto do raio
        int ray_end_screen_x = player_minimap_x_center + (int)(ray_dir_x * dist_along_ray_to_wall * MINIMAP_SCALE);
        int ray_end_screen_y = player_minimap_y_center + (int)(ray_dir_y * dist_along_ray_to_wall * MINIMAP_SCALE);
        draw_line_on_minimap(game, player_minimap_x_center, player_minimap_y_center,
                             ray_end_screen_x, ray_end_screen_y, MINIMAP_RAY_COLOR);
        // --- FIM DO DESENHO DO RAIO NO MINIMAPA ---


        // --- CONTINUAÇÃO DA RENDERIZAÇÃO 3D ---
        int line_height = (int)(game->win_height / perp_wall_dist);
        int draw_start = -line_height / 2 + game->win_height / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + game->win_height / 2;
        if (draw_end >= game->win_height) draw_end = game->win_height - 1;

        int color;
        // ... (sua lógica de cor para paredes 3D aqui, já estava correta)
        if (side == 1) 
            color = 0x00707070; // Mais escuro para paredes Y
        else 
            color = 0x00909090; // Mais claro para paredes X
        
        for (int y_wall = draw_start; y_wall <= draw_end; y_wall++)
        {
            my_mlx_pixel_put_to_image(game, x, y_wall, color);
        }
        // O céu e o chão já foram preenchidos no início da função.
        // Se quiser que eles sejam desenhados *em volta* das paredes (mais preciso):
        /*
        for (int y = 0; y < draw_start; y++)
            my_mlx_pixel_put_to_image(game, x, y, 0x0087CEEB); // Teto
        for (int y = draw_end + 1; y < game->win_height; y++)
            my_mlx_pixel_put_to_image(game, x, y, 0x00228B22); // Chão
        */
        // Mas o preenchimento inicial já cuida disso de forma mais simples.
    }

    mlx_put_image_to_window(game->mlx, game->mlx_w, game->screen_image.img_ptr, 0, 0);
}