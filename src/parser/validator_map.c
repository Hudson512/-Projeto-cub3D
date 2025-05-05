/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:01:09 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/05 10:02:43 by lantonio         ###   ########.fr       */
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
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	init_normalize_map(int *height, int *width, char **map)
{
	*width = max_width(map);
	*height = count_lines(map);
}

char	**normalize_map(char **map, int *out_height, int *out_width)
{
	char	c;
	int		pos[2];
	char	**normalized;

	init_normalize_map(out_height, out_width, map);
	normalized = malloc(sizeof(char *) * (*out_height + 1));
	pos[1] = -1;
	while (++pos[1] < *out_height)
	{
		normalized[pos[1]] = malloc(*out_width + 1);
		pos[0] = -1;
		while (map[pos[1]][++pos[0]])
		{
			c = map[pos[1]][pos[0]];
			normalized[pos[1]][pos[0]] = c;
			if (c == SPACE)
				normalized[pos[1]][pos[0]] = GAP;
		}
		while (pos[0] < *out_width)
			normalized[pos[1]][pos[0]++] = GAP;
		normalized[pos[1]][pos[0]] = '\0';
	}
	normalized[*out_height] = NULL;
	return (normalized);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	flood_fill(char **map, int x, int y)
{
	int	width;
	int	height;

	width = max_width(map);
	height = count_lines(map);
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (map[y][x] == WALL || map[y][x] == FILL)
		return (1);
	if (map[y][x] == GAP)
		return (0);
	map[y][x] = FILL;
	return (
		flood_fill(map, x + 1, y)
		&& flood_fill(map, x - 1, y)
		&& flood_fill(map, x, y + 1)
		&& flood_fill(map, x, y - 1)
	);
}

static void	find_start(char **map, int *dim, int *start)
{
	int		pos[2];
	char	c;

	pos[1] = -1;
	start[0] = -1;
	start[1] = -1;
	while (++pos[1] < dim[1] && start[0] == -1)
	{
		pos[0] = -1;
		while (++pos[0] < dim[0])
		{
			c = map[pos[1]][pos[0]];
			if (c == FLOOR || is_player(c))
			{
				start[0] = pos[0];
				start[1] = pos[1];
				break ;
			}
		}
	}
}

int	is_closed(char **map)
{
	int		dim[2];
	int		start[2];
	int		valid;
	int		i;
	char	**copy;

	copy = normalize_map(map, &dim[1], &dim[0]);
	find_start(copy, dim, start);
	valid = 0;
	if (start[0] != -1)
		valid = flood_fill(copy, start[0], start[1]);
	i = -1;
	while (++i < dim[1])
		free(copy[i]);
	free(copy);
	return (valid);
}

int	is_surrounded(char **map, int rows)
{
	int		i;
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
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' '
			&& map[rows - 1][i] != '\t')
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
