/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:45 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/19 10:24:15 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	map_have_config_duplicate(t_config *config)
{
	if (config->north_texture_set != 1 || config->south_texture_set != 1
		|| config->east_texture_set != 1 || config->west_texture_set != 1
		|| config->floor_color_set != 1 || config->ceiling_color_set != 1)
	{
		parse_exit("Error\nConfiguração duplicada no mapa\n");
		return (1);
	}
	return (0);
}

void	validator_config(t_config *config)
{
	config->map_height = map_rows(config->map);
	config->map_width = map_cols(config->map);
	if (map_have_config_duplicate(config))
		return ;
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
	if (has_invalid_map_char(config->map))
		parse_exit("Mapa contém caracteres inválidos 2\n");
	if (have_valid_wall(config->map) == 0)
		parse_exit("Error\nMapa aberto\n");
	if (config->map_width == 0 || config->map_height == 0)
		parse_exit("Error\nMapa vazio\n");
}
