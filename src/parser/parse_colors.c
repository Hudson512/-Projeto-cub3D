/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:06 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/12 11:20:22 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_quotes(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	return (count);
}

static int	parse_number(char *line, int *i)
{
	int	num;

	if (count_quotes(line) != 2 && line[*i] != ',')
		return (-1);
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (ft_isdigit(line[*i]) != 2048)
		return (-1);
	num = ft_atoi(&line[*i]);
	while (line[*i] && line[*i] != ',')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	return (num);
}

void	capture_color(char *line, t_config *config)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return ;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'F')
	{
		i++;
		config->floor_color.r = parse_number(line, &i);
		config->floor_color.g = parse_number(line, &i);
		config->floor_color.b = parse_number(line, &i);
	}
	else if (line[i] == 'C')
	{
		i++;
		config->ceiling_color.r = parse_number(line, &i);
		config->ceiling_color.g = parse_number(line, &i);
		config->ceiling_color.b = parse_number(line, &i);
	}
}
