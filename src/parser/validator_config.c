/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:45 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 15:34:15 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_have_config_duplicate(t_config *config)
{
	if (config->north_texture_set != 1 || config->south_texture_set != 1
		|| config->east_texture_set != 1 || config->west_texture_set != 1
		|| config->floor_color_set != 1 || config->ceiling_color_set != 1)
	{
		return (1);
	}
	return (0);
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	player_on_border(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
		i++;
	j = -1;
	while (map[0][++j])
		if (is_player(map[0][j]))
			return (1);
	j = -1;
	while (map[i - 1][++j])
		if (is_player(map[i - 1][j]))
			return (1);
	return (0);
}

static int	analyze_map(t_config *config)
{
	config->map_height = map_rows(config->map);
	config->map_width = map_cols(config->map);
	if (config->error_flag == 1)
		parse_exit("Error\nIdentificador de configuração inválido\n");
	if (config->error_flag == 2)
		parse_exit("Error\nLinha de configuração incompleta\n");
	if (map_have_config_duplicate(config))
		parse_exit("Error\nConfiguração duplicada no arquivo\n");
	if (config->map == NULL || config->map[0] == NULL)
		parse_exit("Error\nMapa vazio\n");
	if (config->map_width <= 2 || config->map_height <= 2)
		parse_exit("Error\nMapa muito pequeno\n");
	if (has_invalid_map_char(config->map))
		parse_exit("Error\nMapa contém caracteres inválidos\n");
	if (!have_valid_wall(config->map))
		parse_exit("Error\nMapa aberto\n");
	if (player_on_border(config->map))
		parse_exit("Error\nPlayer na borda do mapa!\n");
	return (0);
}

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
	if (analyze_map(config))
		return ;
}
