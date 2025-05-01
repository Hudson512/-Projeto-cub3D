/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:32 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/01 11:30:58 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	t_color	floor_color;
	t_color	ceiling_color;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_config;

// Parse file
int			check_extension(const char *filename, char *str_ext);
int			validate_map_at_end(const char *filename);
int			is_empty_line(char *line);
void		parse_exit(char *msg);
void		capture_map(char *line, t_config *config);
char		**ft_realloc_map(char **old_map, char *new_line);
int			parse_file(const char *filename, t_config *config);
void		capture_texture(char *line, t_config *config);
void		capture_color(char *line, t_config *config);
void		print_config(t_config *config);
void		capture_position(char **map, t_config *config);
void		validator_config(t_config *config);
int			map_rows(char **map);
int			is_texture_valid(char *texture);
int			check_texture_path(char *path);
int			is_color_valid(t_color color);
int			is_map_closed(char **map, int rows);
int			has_invalid_map_char(char **map);

#endif
