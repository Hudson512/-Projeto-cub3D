/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:13 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/19 10:19:44 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_north_texture(char *line, t_config *config)
{
	config->north_texture = ft_strdup_texture(line);
	collect_mem(config->north_texture);
	if (config->north_texture)
		config->north_texture_set += 1;
}

static void	set_south_texture(char *line, t_config *config)
{
	config->south_texture = ft_strdup_texture(line);
	collect_mem(config->south_texture);
	if (config->south_texture)
		config->south_texture_set += 1;
}

static void	set_west_texture(char *line, t_config *config)
{
	config->west_texture = ft_strdup_texture(line);
	collect_mem(config->west_texture);
	if (config->west_texture)
		config->west_texture_set += 1;
}

static void	set_east_texture(char *line, t_config *config)
{
	config->east_texture = ft_strdup_texture(line);
	collect_mem(config->east_texture);
	if (config->east_texture)
		config->east_texture_set += 1;
}

void	capture_texture(char *line, t_config *config)
{
	char	*tmp;

	tmp = line;
	while (*tmp == ' ' || *tmp == '\t')
		tmp++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_north_texture(tmp + 3, config);
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		set_south_texture(tmp + 3, config);
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		set_west_texture(tmp + 3, config);
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		set_east_texture(tmp + 3, config);
}
