/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:31:30 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 14:48:45 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_ray_x(t_ray *ray)
{
	ray->side_dist_x += ray->delta_dist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

static void	update_ray_y(t_ray *ray)
{
	ray->side_dist_y += ray->delta_dist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

static int	is_wall_hit(t_game *game, t_ray *ray)
{
	if (ray->map_x >= 0 && ray->map_x < game->config.map_width
		&& ray->map_y >= 0 && ray->map_y < game->config.map_height)
	{
		if (game->config.map[ray->map_y]
			&& ray->map_x < (int)ft_strlen(game->config.map[ray->map_y])
			&& game->config.map[ray->map_y][ray->map_x] == '1')
			return (1);
	}
	return (0);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	max_iterations;
	int	iterations;

	max_iterations = game->config.map_width * game->config.map_height * 2;
	iterations = 0;
	while (ray->hit == 0 && iterations < max_iterations)
	{
		iterations++;
		if (ray->side_dist_x < ray->side_dist_y)
			update_ray_x(ray);
		else
			update_ray_y(ray);
		if (is_wall_hit(game, ray))
			ray->hit = 1;
	}
}

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->config.player_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->config.player_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->config.player_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->config.player_y)
			* ray->delta_dist_y;
	}
}
