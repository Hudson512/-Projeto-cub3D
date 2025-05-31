/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:29:51 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/30 20:33:05 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	player_count(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_valid_player(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	capture_position(char **map, t_config *config)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = player_count(map);
	if (count > 1)
		parse_exit("Error\nNúmero inválido de jogadores no mapa\n");
	while (map[i] && count == 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_valid_player(map[i][j]))
			{
				config->player_x = j + 0.5;
				config->player_y = i + 0.5;
				config->player_dir = map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
	parse_exit("Error\nPosição do jogador não encontrada no mapa\n");
}
