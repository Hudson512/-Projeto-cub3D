/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:39:07 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/30 18:47:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_wall_line(t_game *game, t_ray *ray, int x)
{
    t_draw_wall_line vars;
    t_texture *tex;

    // Escolher textura
    if (ray->side == 0 && ray->dir_x < 0)
        tex = &game->textures.west;
    else if (ray->side == 0 && ray->dir_x > 0)
        tex = &game->textures.east;
    else if (ray->side == 1 && ray->dir_y < 0)
        tex = &game->textures.north;
    else
        tex = &game->textures.south;

    // Calcular altura teórica da linha de parede
    int line_height = (int)((game->win_height / ray->perp_wall_dist) * game->fov_scale_factor);

    // Calcular draw_start / draw_end teóricos
    int draw_start = -line_height / 2 + game->win_height / 2;
    int draw_end   =  line_height / 2 + game->win_height / 2;

    // Clamp para dentro da janela
    int start = draw_start < 0 ? 0 : draw_start;
    int end   = draw_end   >= game->win_height ? game->win_height - 1 : draw_end;

    // Calcular posição na textura
    vars.wall_x = (ray->side == 0)
        ? ray->pos_y + ray->perp_wall_dist * ray->dir_y
        : ray->pos_x + ray->perp_wall_dist * ray->dir_x;
    vars.wall_x -= floor(vars.wall_x);
    vars.tex_x = (int)(vars.wall_x * (double)tex->width);
    if ((ray->side == 0 && ray->dir_x > 0)
        || (ray->side == 1 && ray->dir_y < 0))
        vars.tex_x = tex->width - vars.tex_x - 1;

    // Passo da textura e posição inicial (para compensar 
    // parte superior que ficou fora da tela)
    double tex_step = (double)tex->height / (double)line_height;
    double tex_pos = (draw_start < 0)
        ? tex_step * (0 - draw_start)
        : 0.0;

    // Desenho da linha entre start e end
    for (int y = start; y <= end; y++)
    {
        int tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        else if (tex_y >= tex->height)
            tex_y = tex->height - 1;

        size_t offset = tex_y * tex->line_length + vars.tex_x * (tex->bpp / 8);
        int color = *(int *)(tex->addr + offset);
        my_mlx_pixel_put_to_image(game, x, y, color);

        tex_pos += tex_step;
    }
}

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	(void)game;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
}
