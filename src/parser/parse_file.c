/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:59 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/01 10:36:58 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Criar a funcao parse_file(argv[1], &config)

#include "../../includes/cub3d.h"

int parse_file(const char *filename, t_config *config)
{
    char *line;
    int fd;

    config->map = NULL;
    if (!check_extension(filename))
        return (ft_putstr_fd("Error\nArquivo deve ter a extensao .cub\n", 2), 1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Error\nNao foi possivel abrir o arquivo\n", 2), 1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        capture_texture(line, config);
        capture_color(line, config);
        capture_map(line, config);
        free(line);
        line = get_next_line(fd);
    }
    collect_mem(config->map);
    capture_position(config->map, config);
    close(fd);
    validator_config(config);
    return (0);
}

void print_config(t_config *config)
{
    int i;

    i = 0;
    printf("North Texture: %s", config->north_texture);
    printf("South Texture: %s", config->south_texture);
    printf("West Texture: %s", config->west_texture);
    printf("East Texture: %s\n", config->east_texture);
    printf("Floor Color: %d, %d, %d\n", config->floor_color.r, config->floor_color.g, config->floor_color.b);
    printf("Ceiling Color: %d, %d, %d\n", config->ceiling_color.r, config->ceiling_color.g, config->ceiling_color.b);
    printf("\nMap:\n");
    while (config->map && config->map[i])
    {
        printf("%s", config->map[i]);
        printf("\n");
        i++;
    }
}
