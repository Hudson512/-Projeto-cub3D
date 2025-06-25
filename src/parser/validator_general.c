/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:20:16 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 16:02:47 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_identifier(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	is_empty_or_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

static int	is_map_line(const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0');
}

static int	has_content_after_identifier(const char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line || *line == '\n')
		return (0);
	return (1);
}

void	validate_config_line(char *line, t_config *config)
{
	char	*trimmed;
	int		len;

	if (is_empty_or_whitespace(line))
		return ;
	trimmed = line;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (is_map_line(trimmed))
		return ;
	len = ft_strlen(trimmed);
	if (len > 0 && trimmed[len - 1] == '\n')
		len--;
	if (len == 0)
		return ;
	if (!is_valid_identifier(trimmed))
	{
		config->error_flag = 1;
		return ;
	}
	if (!has_content_after_identifier(trimmed + 2))
	{
		config->error_flag = 1;
		return ;
	}
}
