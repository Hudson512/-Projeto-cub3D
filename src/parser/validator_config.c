/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:45 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/01 12:40:47 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	validator_config(t_config *config)
{
	if (!is_texture_valid(config->north_texture))
		parse_exit("Error\nCaminho da textura do Norte inválido\n");
	if (!is_texture_valid(config->south_texture))
		parse_exit("Error\nCaminho da textura do Sul inválido\n");
	if (!is_texture_valid(config->west_texture))
		parse_exit("Error\nCaminho da textura do Oeste inválido\n");
	if (!is_texture_valid(config->east_texture))
		parse_exit("Error\nCaminho da textura do Leste inválido\n");
	if (!is_color_valid(config->floor_color))
		parse_exit("Error\nCor do chão inválida\n");
	if (!is_color_valid(config->ceiling_color))
		parse_exit("Error\nCor do teto inválida\n");
    
	// Verificar se o mapa esta fechado por paredes (1) # Melhorar essa parte amanhã
	if (has_invalid_map_char(config->map))
		parse_exit("Error\nMapa não está fechado por paredes ou contém caracteres inválidos\n");
	// Verifica se o jogador está dentro do mapa
}
