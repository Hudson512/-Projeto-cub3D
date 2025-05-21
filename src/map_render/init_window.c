/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:27 by lantonio          #+#    #+#             */
/*   Updated: 2025/05/20 12:53:43 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Função para lidar com o evento de fechar a janela (clicar no 'X')
static int close_window_x(t_game *game)
{
    if (game && game->mlx && game->mlx_w){
        mlx_destroy_window(game->mlx, game->mlx_w);
    }
	sucess_exit("Janela fechada!\n");
    exit(0);
    return (0);
}

static void init_player_direction(t_game *game)
{
    if (!game)
        return;

    // Definir velocidades (ajuste conforme necessário)
    game->move_speed = 0.05; // Quão rápido o jogador se move por frame/keypress
    game->rot_speed = 0.03;  // Quão rápido o jogador gira por frame/keypress

    if (game->config.player_dir == 'N')
    {
        game->dir_x = 0;
        game->dir_y = -1; // Olhando para cima no mapa (Y negativo)
        game->plane_x = 0.66;
        game->plane_y = 0;
    }
    else if (game->config.player_dir == 'S')
    {
        game->dir_x = 0;
        game->dir_y = 1;  // Olhando para baixo no mapa (Y positivo)
        game->plane_x = -0.66; // Invertido em relação a 'N'
        game->plane_y = 0;
    }
    else if (game->config.player_dir == 'W') // Oeste
    {
        game->dir_x = -1; // Olhando para a esquerda no mapa (X negativo)
        game->dir_y = 0;
        game->plane_x = 0;
        game->plane_y = -0.66; // Note a troca e o sinal para manter perpendicularidade
    }
    else if (game->config.player_dir == 'E') // Leste
    {
        game->dir_x = 1;  // Olhando para a direita no mapa (X positivo)
        game->dir_y = 0;
        game->plane_x = 0;
        game->plane_y = 0.66;
    }
}

void my_mlx_pixel_put_to_image(t_game *game, int x, int y, int color)
{
    char *dst;

    if (!game || !game->screen_image.addr)
        return;

    // Verifica se x e y estão dentro dos limites da imagem para evitar segfault
    if (x < 0 || x >= game->win_width || y < 0 || y >= game->win_height)
        return;

    dst = game->screen_image.addr + (y * game->screen_image.line_length + x * (game->screen_image.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static void player_move(t_game *game, double move_x_component, double move_y_component)
{
    double new_player_x;
    double new_player_y;
    int map_check_x;
    int map_check_y;

    // Verifica se os ponteiros e o mapa são válidos
    if (!game || !game->config.map)
        return;

    // Calcula a nova posição potencial do jogador
    new_player_x = game->config.player_x + move_x_component;
    new_player_y = game->config.player_y + move_y_component;

    // Determina a célula do mapa para verificar a colisão
    map_check_x = (int)new_player_x;
    map_check_y = (int)new_player_y;

    // Verificação de colisão:
    // 1. Verifica se a nova posição está dentro dos limites do mapa.
    // 2. Verifica se a linha game->config.map[map_check_y] é válida.
    // 3. Verifica se a coluna map_check_x é válida para a linha atual.
    // 4. Verifica se a célula de destino não é uma parede ('1').
    if (map_check_y >= 0 && map_check_y < game->config.map_height &&
        game->config.map[map_check_y] != NULL && // Garante que a linha do mapa foi alocada
        map_check_x >= 0 && map_check_x < (int)ft_strlen(game->config.map[map_check_y]) && // Usa ft_strlen para a largura real da linha
        game->config.map[map_check_y][map_check_x] != '1')
    {
        // Se não houver colisão, atualiza a posição do jogador
        game->config.player_x = new_player_x;
        game->config.player_y = new_player_y;
    }
    // Opcional: Implementar "deslizamento de parede" aqui.
    // Se a verificação acima falhar, você pode tentar mover apenas no eixo X
    // e depois (ou independentemente) apenas no eixo Y.
    // Isso permite que o jogador deslize ao longo das paredes em vez de parar completamente.
    // Por simplicidade, esta versão básica para ao encontrar um obstáculo na direção do movimento.
}

static void player_rotate(t_game *game, double angle)
{
    double old_dir_x;
    double old_plane_x;

    if (!game)
        return;

    // Rotaciona o vetor de direção
    old_dir_x = game->dir_x;
    game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
    game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);

    // Rotaciona o vetor do plano da câmera
    old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
    game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}


int handle_keypress(int keycode, t_game *game)
{
    if (!game) // Verificação de segurança
        return (1);

    // Descomente a linha abaixo para descobrir os keycodes no seu sistema ao pressionar teclas
    // printf("Key pressed: %d\n", keycode);

    if (keycode == KEY_ESC)
        close_window_x(game); // Reutiliza sua função para fechar a janela
    else if (keycode == KEY_W) // Mover para frente
        player_move(game, game->dir_x * game->move_speed, game->dir_y * game->move_speed);
    else if (keycode == KEY_S) // Mover para trás
        player_move(game, -game->dir_x * game->move_speed, -game->dir_y * game->move_speed);
    else if (keycode == KEY_A) // Strafe para a esquerda (movimento lateral)
        // Para strafe, move-se ao longo do vetor do plano da câmera
        player_move(game, -game->plane_x * game->move_speed, -game->plane_y * game->move_speed);
    else if (keycode == KEY_D) // Strafe para a direita
        player_move(game, game->plane_x * game->move_speed, game->plane_y * game->move_speed);
    else if (keycode == KEY_LEFT_ARROW) // Rotacionar para a esquerda
        player_rotate(game, -game->rot_speed); // Ângulo negativo para rotação anti-horária
    else if (keycode == KEY_RIGHT_ARROW) // Rotacionar para a direita
        player_rotate(game, game->rot_speed);  // Ângulo positivo para rotação horária
    else
        return (0); // Se não for uma tecla de interesse, não faz nada e não redesenha

    // Após qualquer movimento ou rotação que altere o estado do jogador,
    // é crucial redesenhar a cena para que as mudanças sejam visíveis.
    render_next_frame(game);

    return (0); // Indica que o evento foi processado com sucesso
}


void	init_window(t_game *game)
{
    int screen_w;
	int screen_h;
	int window_w;
	int window_h;

    // Obter tamanho máximo da tela
    mlx_get_screen_size(game->mlx, &screen_w, &screen_h);

    // Calcular o tamanho desejado da janela com base no mapa
	window_w = game->config.map_width * TILE_SIZE;
	window_h = game->config.map_height * TILE_SIZE;

	// Garantir que a janela não ultrapasse a tela
	if (window_w > screen_w)
		window_w = screen_w;
	if (window_h > screen_h)
		window_h = screen_h;
    // Inicializar a janela MLX (estava faltando)
    game->mlx_w = mlx_new_window(game->mlx, window_w, window_h, "Cub3D");
    if (!game->mlx_w)
    {
        error_exit("Erro\n ao criar janela\n");
    }
    
	init_player_direction(game);
	
	// Definir dimensões da janela
	// game->win_width = game->config.map_width * TILE_SIZE;
	// game->win_height = game->config.map_height * TILE_SIZE;
    game->win_width = window_w;     // Usar a largura efetiva da janela
    game->win_height = window_h;

	// Criar imagem para o renderizador
	game->screen_image.img_ptr = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (!game->screen_image.img_ptr)
	{
	    error_exit("Erro\n ao criar imagem\n");
	}
	
	game->screen_image.addr = mlx_get_data_addr(game->screen_image.img_ptr,
											&game->screen_image.bits_per_pixel,
											&game->screen_image.line_length,
											&game->screen_image.endian);
	if (!game->screen_image.addr)
	{
	    error_exit("Erro\n ao obter endereço de dados da imagem\n");
	}
	
	// Configurar hooks
	mlx_hook(game->mlx_w, 17, 0, close_window_x, game);
    mlx_hook(game->mlx_w, 2, 1L << 0, handle_keypress, game);
	
	// Renderizar o primeiro frame
	render_next_frame(game);
	
	// Iniciar o loop do MLX
	mlx_loop(game->mlx);
}
