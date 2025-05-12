/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:32 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:02 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WALL '1'
# define FLOOR '0'
# define PLAYER_CHARS "NSEW"
# define FILL 'X'
# define SPACE ' '
# define GAP '9'

# define SPEED 5
# define PI 3.14159265359
# define PI2 3.14159265359/2
# define PI3 3*3.14159265359/2
# define DR 0.0174533

# define RAY_WIDTH 8

# define DEBUG 1
# define CLEAR 1
# define AUTOWIDTH 0

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

typedef struct s_game
{
	void		*mlx;
	void		*mlx_w;
	int			player_pos_x;
	int			player_pos_y;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	float		ca;
	int			screen_width;
	int			screen_height;
	int			map_x;
	int			map_y;
	int			map_s;
	int			player_fov;
	t_config	config;
}				t_game;

typedef struct s_render
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
	float	nTan;
	float	disH;
	float	hx;
	float	hy;
	float	disV;
	float	vx;
	float	vy;
	float	lineH;
	float	lineO;
	float	disT;
	int		color;
}			t_render;

typedef struct s_draw_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}		t_draw_line;

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
int			have_valid_wall(char **map);

int			free_matrix(char **mat);
int			has_invalid_map_char(char **map);

// Window initialization
void		init_window(t_game *game);

// Keyboard events handler
int			key_press_handler(int keycode, t_game *game);
void		a_press_handler(t_game *game);
void		w_press_handler(t_game *game);
void		d_press_handler(t_game *game);
void		s_press_handler(t_game *game);
void		right_press_handler(t_game *game);
void		left_press_handler(t_game *game);

// game drawing
void		draw(t_game *game);
void		draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void		draw_square(t_game *game, int x, int y, int color);
void		draw_map(t_game *game, int *map);
void		draw_3d(t_game *game, t_render render);
void		draw_pfov(t_game *game);
void		draw_player(t_game *game);

#endif
