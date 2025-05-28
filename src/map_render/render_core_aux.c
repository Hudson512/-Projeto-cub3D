/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:39:07 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 11:39:45 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)((game->win_height / ray->perp_wall_dist)
			* game->fov_scale_factor);
	draw_start = -line_height / 2 + game->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->win_height / 2;
	if (draw_end >= game->win_height)
		draw_end = game->win_height - 1;
	color = 0x00909090;
	if (ray->side == 1)
		color = 0x00707070;
	y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put_to_image(game, x, y, color);
		y++;
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
