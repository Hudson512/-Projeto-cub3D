/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:54:27 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/23 12:27:00 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Verifica se o caractere é um dos válidos para o mapa
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

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || !*line)
		return (0);
	while (line[i] == ' ')
		i++;
	return (line[i] == '1');
}

int	validate_map_at_end(const char *file_path)
{
	int		fd;
	char	*line;
	int		in_map;

	in_map = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nNao foi possivel abrir o arquivo\n", 2), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!in_map && is_map_line(line))
			in_map = 1;
		else if (in_map && !is_map_line(line) && !is_empty_line(line))
		{
			free(line);
			close(fd);
			ft_putstr_fd("Error\nErro na configuração do mapa\n", 2);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
