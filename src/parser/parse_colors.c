/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:06 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/11 15:24:24 by lantonio         ###   ########.fr       */
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

static int	check_digit_count(char *line, int start)
{
	int	count;
	int	i;

	i = start;
	count = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) != 1)
		return (-1);
	while (line[i] && ft_isdigit(line[i]))
	{
		count++;
		i++;
	}
	if (count <= 3)
		return (count);
	return (-1);
}

static int	is_digit_string(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ',' && line[i] != '\n' && i < 3)
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		i++;
	}
	if (i == 0 || i > 3)
		return (0);
	return (1);
}

static int	parse_number(char *line, int *i)
{
	int	num;

	if (count_quotes(line) != 2 && line[*i] != ',')
		return (-1);
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (is_digit_string(&line[*i]) == 0 || check_digit_count(line, *i) == -1)
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
