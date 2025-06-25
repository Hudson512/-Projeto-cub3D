/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:16 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 12:25:45 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(const char *filename, char *str_ext)
{
	size_t	str_len;
	size_t	suffix_len;

	str_len = ft_strlen(filename);
	suffix_len = ft_strlen(str_ext);
	if (suffix_len >= str_len)
		return (0);
	return (ft_strncmp(filename + str_len - suffix_len, str_ext,
			suffix_len) == 0 && filename[str_len - suffix_len - 1] != '/'
		&& filename[str_len - suffix_len - 1] != '.');
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	free_matrix(char **mat)
{
	int	i;

	i = -1;
	if (mat != NULL)
	{
		while (mat && mat[++i])
			free(mat[i]);
		free(mat);
	}
	return (i);
}

int	has_invalid_map_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map || !*map)
		return (1);
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
