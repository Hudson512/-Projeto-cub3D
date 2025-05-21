/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:59:32 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/19 09:36:30 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Adicione estas definições no início do seu init_window.c ou em cub3d.h
#define MINIMAP_SCALE 5          // Quantos pixels na tela para cada célula do mapa no minimapa
#define MINIMAP_OFFSET_X 10      // Deslocamento X para o canto superior esquerdo do minimapa
#define MINIMAP_OFFSET_Y 10      // Deslocamento Y para o canto superior esquerdo do minimapa
#define MINIMAP_PLAYER_SIZE 3    // Tamanho do quadrado/ponto do jogador no minimapa
#define MINIMAP_WALL_COLOR 0x00fefefe   // Cinza escuro para paredes do minimapa
#define MINIMAP_FLOOR_COLOR 0x00000000  // Cinza claro para chão do minimapa
#define MINIMAP_PLAYER_COLOR 0x00FF0000 // Vermelho para o jogador
#define MINIMAP_RAY_COLOR 0x0000FF00    // Verde para os raios
#define MINIMAP_FOV_COLOR 0x000000FF   // Azul para as linhas do campo de visão (opcional)

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT_ARROW 65361
#define KEY_RIGHT_ARROW 65363

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
	double			player_x;
	double			player_y;
	char		player_dir;
}				t_config;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_w;

	// Novos campos para direção e plano da câmera
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;

    // Velocidades
    double move_speed;
    double rot_speed;

	int     win_width;
    int     win_height;


	t_config	config;
	t_img   screen_image;
}				t_game;



// Parse file
int				check_extension(const char *filename, char *str_ext);
int				validate_map_at_end(const char *filename);
int				is_empty_line(char *line);
void			parse_exit(char *msg);
void			sucess_exit(char *msg);
void	error_exit(char *msg);
void			capture_map(char *line, t_config *config);
char			**ft_realloc_map(char **old_map, char *new_line);
int				parse_file(const char *filename, t_config *config);
void			capture_texture(char *line, t_config *config);
void			capture_color(char *line, t_config *config);
void			print_config(t_config *config);
void			capture_position(char **map, t_config *config);
void			validator_config(t_config *config);
int				map_rows(char **map);
int				map_cols(char **map);
int				is_texture_valid(char *texture);
int				check_texture_path(char *path);
int				is_color_valid(t_color color);
int				have_valid_wall(char **map);

int				free_matrix(char **mat);
int				has_invalid_map_char(char **map);

// Window initialization
void			init_window(t_game *game);
void 			render_next_frame(t_game *game);
void 			my_mlx_pixel_put_to_image(t_game *game, int x, int y, int color);

// minimap
void draw_minimap_square(t_game *game, int top_left_x, int top_left_y, int size, int color);
void draw_minimap_background(t_game *game);
void draw_player_on_minimap(t_game *game);
void draw_line_on_minimap(t_game *game, int x0, int y0, int x1, int y1, int color);




#endif
