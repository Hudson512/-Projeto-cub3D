/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:01:09 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/02 10:01:21 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	max_width(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		int len = strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char **normalize_map(char **map, int *out_height, int *out_width) {
	int h = count_lines(map);
	int w = max_width(map);
	*out_height = h;
	*out_width = w;

	char **normalized = malloc(sizeof(char *) * (h + 1));
	for (int y = 0; y < h; y++) {
		normalized[y] = malloc(w + 1);
		int x = 0;
		for (; map[y][x]; x++) {
			char c = map[y][x];
			if (c == SPACE)
				normalized[y][x] = GAP;
			else
				normalized[y][x] = c;
		}
		while (x < w)
			normalized[y][x++] = GAP;
		normalized[y][x] = '\0';
	}
	normalized[h] = NULL;
	return normalized;
}

int is_player(char c) {
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int flood_fill(char **map, int x, int y, int width, int height) {
	if (x < 0 || y < 0 || x >= width || y >= height)
		return 0;
	if (map[y][x] == WALL || map[y][x] == FILL)
		return 1;
	if (map[y][x] == GAP)
		return 0;

	map[y][x] = FILL;

	return (
		flood_fill(map, x + 1, y, width, height) &&
		flood_fill(map, x - 1, y, width, height) &&
		flood_fill(map, x, y + 1, width, height) &&
		flood_fill(map, x, y - 1, width, height)
	);
}

int is_closed(char **map)
{
	int width, height;
	char **copy = normalize_map(map, &height, &width);

	// Localiza ponto de partida válido (0 ou N/S/E/W)
	int start_x = -1, start_y = -1;
	for (int y = 0; y < height && start_x == -1; y++) {
		for (int x = 0; x < width; x++) {
			char c = copy[y][x];
			if (c == FLOOR || is_player(c)) {
				start_x = x;
				start_y = y;
				break;
			}
		}
	}

	int valid = 0;
	if (start_x != -1)
		valid = flood_fill(copy, start_x, start_y, width, height);

	// liberar memória
	for (int y = 0; y < height; y++)
		free(copy[y]);
	free(copy);

	return valid;
}

int	is_surrounded(char **map, int rows)
{
	int	i;
	char	*line;

	i = -1;
	line = NULL;
	while (map[++i])
	{
		line = ft_strtrim(map[i], " ");
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			return (free(line), 0);
		free(line);
	}
	i = -1;
	while (map[0][++i])
		if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\t')
			return (0);
	i = -1;
	while (map[rows - 1][++i])
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' ' && map[rows - 1][i] != '\t')
			return (0);
	return (1);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	has_invalid_map_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
