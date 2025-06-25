/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:06 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 13:23:06 by hmateque         ###   ########.fr       */
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
	num = ft_atoi_color(&line[*i]);
	while (line[*i] && line[*i] != ',')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	return (num);
}

static void	set_floor_color(char *line, t_config *config, int *i)
{
	(*i)++;
	config->floor_color.r = parse_number(line, i);
	config->floor_color.g = parse_number(line, i);
	config->floor_color.b = parse_number(line, i);
	if (config->floor_color.r != -1 && config->floor_color.g != -1
		&& config->floor_color.b != -1)
		config->floor_color_set += 1;
}

static void	set_ceiling_color(char *line, t_config *config, int *i)
{
	(*i)++;
	config->ceiling_color.r = parse_number(line, i);
	config->ceiling_color.g = parse_number(line, i);
	config->ceiling_color.b = parse_number(line, i);
	if (config->ceiling_color.r != -1 && config->ceiling_color.g != -1
		&& config->ceiling_color.b != -1)
		config->ceiling_color_set += 1;
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
		set_floor_color(line, config, &i);
	}
	else if (line[i] == 'C')
	{
		set_ceiling_color(line, config, &i);
	}
}
