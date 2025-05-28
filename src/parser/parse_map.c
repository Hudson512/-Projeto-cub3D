/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:09 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 10:05:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**ft_realloc_map(char **old_map, char *new_line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (old_map && old_map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (old_map && old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i++] = ft_strdup(new_line);
	collect_mem(new_map[i - 1]);
	new_map[i] = NULL;
	free(old_map);
	return (new_map);
}

void	capture_map(char *line, t_config *config)
{
	char	*tmp;

	if (line == NULL)
		return ;
	tmp = line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (is_empty_line(line) || ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return ;
	config->map = ft_realloc_map(config->map, tmp);
}

int	map_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	map_cols(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map && map[i])
	{
		if ((int)ft_strlen(map[i]) > j)
			j = ft_strlen(map[i]);
		i++;
	}
	return (j);
}
