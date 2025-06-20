/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:39:07 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/20 09:43:57 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_texture	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x < 0)
		return (&game->textures.east);
	else if (ray->side == 0 && ray->dir_x > 0)
		return (&game->textures.west);
	else if (ray->side == 1 && ray->dir_y < 0)
		return (&game->textures.south);
	return (&game->textures.north);
}

static void	calculate_wall_dimensions(t_game *game, t_ray *ray,
		t_draw_wall_line *vars)
{
	vars->line_height = (int)((game->win_height / ray->perp_wall_dist)
			* game->fov_scale_factor);
	vars->draw_start = -vars->line_height / 2 + game->win_height / 2;
	vars->draw_end = vars->line_height / 2 + game->win_height / 2;
	vars->start = vars->draw_start;
	if (vars->draw_start < 0)
		vars->start = 0;
	vars->end = vars->draw_end;
	if (vars->draw_end >= game->win_height)
		vars->end = game->win_height - 1;
}

static void	calculate_texture_position(t_ray *ray, t_draw_wall_line *vars,
		t_texture *tex)
{
	vars->wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	if (ray->side == 0)
	{
		vars->wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	}
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		vars->tex_x = tex->width - vars->tex_x - 1;
	vars->tex_step = (double)tex->height / (double)vars->line_height;
	vars->tex_pos = 0.0;
	if (vars->draw_start < 0)
		vars->tex_pos = vars->tex_step * (0 - vars->draw_start);
}

void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	t_draw_wall_line	vars;
	t_texture			*tex;

	tex = select_texture(game, ray);
	calculate_wall_dimensions(game, ray, &vars);
	calculate_texture_position(ray, &vars, tex);
	vars.y = vars.start;
	while (vars.y <= vars.end)
	{
		vars.tex_y = (int)vars.tex_pos;
		if (vars.tex_y < 0)
			vars.tex_y = 0;
		else if (vars.tex_y >= tex->height)
			vars.tex_y = tex->height - 1;
		vars.offset = vars.tex_y * tex->line_length + vars.tex_x * (tex->bpp
				/ 8);
		vars.color = *(int *)(tex->addr + vars.offset);
		my_mlx_pixel_put_to_image(game, x, vars.y, vars.color);
		vars.tex_pos += vars.tex_step;
		vars.y++;
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
