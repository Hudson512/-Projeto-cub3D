/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:59 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 15:39:01 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->east_texture = NULL;
	config->west_texture = NULL;
	config->floor_color.r = -1;
	config->floor_color.g = -1;
	config->floor_color.b = -1;
	config->ceiling_color.r = -1;
	config->ceiling_color.g = -1;
	config->ceiling_color.b = -1;
	config->map = NULL;
	config->map_width = 0;
	config->map_height = 0;
	config->player_x = 0;
	config->player_y = 0;
	config->player_dir = '\0';
	config->map_started = 0;
	config->found_empty = 0;
	config->floor_color_set = 0;
	config->ceiling_color_set = 0;
	config->north_texture_set = 0;
	config->south_texture_set = 0;
	config->west_texture_set = 0;
	config->east_texture_set = 0;
	config->error_flag = 0;
}

int	parse_file(const char *filename, t_config *config)
{
	char	*line;
	int		fd;

	init_config(config);
	if (!check_extension(filename, ".cub"))
		return (ft_putstr_fd("Error\nArquivo deve ter a extensao .cub\n", 2), 1);
	if (!validate_map_at_end(filename, 0))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nNao foi possivel abrir o arquivo\n", 2),
			1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		validate_config_line(line, config);
		(capture_texture(line, config), capture_color(line, config));
		(capture_map(line, config), free(line));
		line = get_next_line(fd);
	}
	(close(fd), collect_mem(config->map));
	(validator_config(config), capture_position(config->map, config));
	return (0);
}

void	print_config(t_config *config)
{
	int	i;

	i = 0;
	printf("North Texture: %s\n", config->north_texture);
	printf("South Texture: %s\n", config->south_texture);
	printf("West Texture: %s\n", config->west_texture);
	printf("East Texture: %s\n", config->east_texture);
	printf("Floor Color: %d, %d, %d\n", config->floor_color.r,
		config->floor_color.g, config->floor_color.b);
	printf("Ceiling Color: %d, %d, %d\n", config->ceiling_color.r,
		config->ceiling_color.g, config->ceiling_color.b);
	printf("\nMap:\n");
	while (config->map && config->map[i])
	{
		printf("%s", config->map[i]);
		printf("\n");
		i++;
	}
}

// print_map
void	print_map(t_config *config)
{
	int	i;

	i = 0;
	if (!config->map)
	{
		printf("Mapa vazio\n");
		return ;
	}
	while (config->map[i])
	{
		printf("%s\n", config->map[i]);
		i++;
	}
}
