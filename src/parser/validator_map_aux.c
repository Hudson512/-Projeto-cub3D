/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:54:27 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 12:27:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Verifica se o caractere é um dos válidos para o mapa
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || !*line)
		return (0);
	while (line[i] == ' ')
		i++;
	return (line[i] == '1' || line[i] == '0');
}

static void	process_line(char *line, int *in_map, int *end_map, int *error)
{
	if (!*in_map && is_map_line(line))
		*in_map = 1;
	else if (*in_map && is_empty_line(line))
		*end_map = 1;
	else if ((*end_map && !is_empty_line(line)) || (*in_map
			&& !is_map_line(line) && !is_empty_line(line)))
	{
		ft_putstr_fd("Error\nConteúdo inválido após o mapa\n", 2);
		*error = 1;
	}
}

static void	clear_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	validate_map_at_end(const char *file_path, int error)
{
	int		fd;
	char	*line;
	int		in_map;
	int		end_map;

	in_map = 0;
	end_map = 0;
	error = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nNao foi possivel abrir o arquivo\n", 2),
			0);
	line = get_next_line(fd);
	while (line != NULL && !error)
	{
		process_line(line, &in_map, &end_map, &error);
		free(line);
		if (!error)
			line = get_next_line(fd);
	}
	clear_remaining_lines(fd);
	close(fd);
	if (error)
		return (0);
	return (1);
}
