/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:13 by hmateque          #+#    #+#             */
/*   Updated: 2025/04/29 12:14:27 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	capture_texture(char *line, t_config *config)
{
	if (is_empty_line(line))
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		config->north_texture = ft_strdup(line + 3);
		collect_mem(config->north_texture);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		config->south_texture = ft_strdup(line + 3);
		collect_mem(config->south_texture);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		config->west_texture = ft_strdup(line + 3);
		collect_mem(config->west_texture);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		config->east_texture = ft_strdup(line + 3);
		collect_mem(config->east_texture);
	}
}
