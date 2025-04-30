/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:09 by hmateque          #+#    #+#             */
/*   Updated: 2025/04/30 14:19:14 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	capture_map(char *line, t_config *config)
{
	if (is_empty_line(line) || ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
        || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
        || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return ;
	config->map = ft_realloc_map(config->map, line);
}

static char	*ft_strdup_map(const char *s)
{
	char	*dest;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	dest = ft_calloc(1, len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_realloc_map(char **old_map, char *new_line)
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
	new_map[i++] = ft_strdup_map(new_line);
	collect_mem(new_map[i - 1]);
	new_map[i] = NULL;
	free(old_map);
	return (new_map);
}

int map_rows(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}