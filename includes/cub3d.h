/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:32 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/16 09:54:43 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MINIMAP_SCALE 5
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define MINIMAP_PLAYER_SIZE 3
# define MINIMAP_WALL_COLOR 0x00fefefe
# define MINIMAP_FLOOR_COLOR 0x00000000
# define MINIMAP_PLAYER_COLOR 0x00FF0000
# define MINIMAP_RAY_COLOR 0x0000FF00
# define MINIMAP_FOV_COLOR 0x000000FF

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT_ARROW 65361
# define KEY_RIGHT_ARROW 65363
# define KEY_PLUS 65362
# define KEY_MINUS 65364

# define ZOOM_FACTOR 0.1
# define MIN_PLANE_ACTIVE_COMPONENT 0.05
# define MAX_PLANE_ACTIVE_COMPONENT 5.0

# define TILE_SIZE 64

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}				t_textures;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	double		player_x;
	double		player_y;
	char		player_dir;
	int			map_started;
	int			found_empty;
	int			floor_color_set;
	int			ceiling_color_set;
	int			north_texture_set;
	int			south_texture_set;
	int			west_texture_set;
	int			east_texture_set;
}				t_config;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_w;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			win_width;
	int			win_height;
	int			minimap;
	int			zoom;
	double		fov_scale_factor;
	t_config	config;
	t_img		screen_image;
	t_textures	textures;
}				t_game;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
}				t_ray;

typedef struct s_draw
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_draw;

typedef struct s_draw_wall_line
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			start;
	int			end;
	double		wall_x;
	int			y;
	int			d;
	int			tex_x;
	int			tex_y;
	size_t		offset;
	int			color;
	double		tex_step;
	double		tex_pos;
}				t_draw_wall_line;

// functions auxiliary
char			*ft_strdup_texture(const char *s);
int				check_digit_count(char *line, int start);
int				is_digit_string(char *line);

// validation general
int				is_empty_line(char *line);
int				free_matrix(char **mat);
void			print_config(t_config *config);

// Parse file
int				parse_file(const char *filename, t_config *config);

// validation map
int				check_extension(const char *filename, char *str_ext);
int				validate_map_at_end(const char *filename);
void			validator_config(t_config *config);
int				is_texture_valid(char *texture);
int				check_texture_path(char *path);
int				is_color_valid(t_color color);
int				has_invalid_map_char(char **map);
int				have_valid_wall(char **map);

// capture map data
void			capture_texture(char *line, t_config *config);
void			capture_color(char *line, t_config *config);
void			capture_map(char *line, t_config *config);
void			capture_position(char **map, t_config *config);
int				map_rows(char **map);
int				map_cols(char **map);

// Exit functions
void			parse_exit(char *msg);
void			sucess_exit(char *msg);
void			error_exit(char *msg);
int				close_window_x(t_game *game);

// Window initialization
void			init_window(t_game *game);

// Rendering 3D
void			render_next_frame(t_game *game);
void			calculate_wall_distance(t_game *game, t_ray *ray);
void			draw_wall_line(t_game *game, t_ray *ray, int x);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_step_and_side_dist(t_game *game, t_ray *ray);

// minimap
void			render_minimap(t_game *game);
void			draw_minimap_square(t_game *game, int *top_left, int size,
					int color);
void			draw_minimap_background(t_game *game);
void			draw_player_on_minimap(t_game *game);
void			draw_line_on_minimap(t_game *game, int *x, int *y);

// Pixel manipulation
void			my_mlx_pixel_put_to_image(t_game *game, int x, int y,
					int color);

// Eventos
int				handle_keypress(int keycode, t_game *game);

// Player moves and placement
void			player_rotate(t_game *game, double angle);
void			player_move(t_game *game, double move_x_component,
					double move_y_component);
void			handle_zoom_out(t_game *game);
void			handle_zoom_in(t_game *game);
void			init_player_direction(t_game *game);

#endif
