/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:39:07 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 15:08:16 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	t_draw_wall_line	vars;
	t_texture			*tex;

	if (ray->side == 0 && ray->dir_x < 0)
		tex = &game->textures.west;
	else if (ray->side == 0 && ray->dir_x > 0)
		tex = &game->textures.east;
	else if (ray->side == 1 && ray->dir_y < 0)
		tex = &game->textures.north;
	else
		tex = &game->textures.south;
	vars.line_height = (int)((game->win_height / ray->perp_wall_dist) * game->fov_scale_factor);
	vars.draw_start = -vars.line_height / 2 + game->win_height / 2;
	if (vars.draw_start < 0)
		vars.draw_start = 0;
	vars.draw_end = vars.line_height / 2 + game->win_height / 2;
	if (vars.draw_end >= game->win_height)
		vars.draw_end = game->win_height - 1;
	if (ray->side == 0)
		vars.wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		vars.wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	vars.wall_x -= floor(vars.wall_x);
	vars.tex_x = (int)(vars.wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		vars.tex_x = tex->width - vars.tex_x - 1;
	vars.y = vars.draw_start;
	while (vars.y <= vars.draw_end)
	{
		vars.d = vars.y * 256 - game->win_height * 128 + vars.line_height * 128;
		vars.tex_y = ((vars.d * tex->height) / vars.line_height) / 256;
		vars.offset = vars.tex_y
			* tex->line_length + vars.tex_x * (tex->bpp / 8);
		vars.color = *(int *)(tex->addr + vars.offset);
		my_mlx_pixel_put_to_image(game, x, vars.y, vars.color);
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
