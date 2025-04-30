/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:01:09 by hmateque          #+#    #+#             */
/*   Updated: 2025/04/30 14:34:39 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_map_closed(char **map, int rows)
{
	int	i;
	int	j;

	// verificar o topo e o fundo do mapa
	for (j = 0; j < rows; j++)
	{
		if (map[0][j] != '1' && !is_space(map[0][j]))
			return (0);
		if (map[rows - 1][j] != '1' && !is_space(map[rows - 1][j]))
			return (0);
	}
	// verificar as laterais do mapa
	for (i = 0; i < rows; i++)
	{
		if (map[i][0] != '1' && !is_space(map[i][0]))
			return (0);
		if (map[i][j - 1] != '1' && !is_space(map[i][j - 1]))
			return (0);
	}
	return (1);
}
