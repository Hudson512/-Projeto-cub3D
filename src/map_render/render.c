/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:43:34 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/28 11:33:22 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	rgb_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	init_ray_values(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->config.player_x;
	ray->map_y = (int)game->config.player_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	ray->hit = 0;
	ray->side = 0;
}

static void	fill_background(t_game *game)
{
	int	y_fill;
	int	x_fill;

	y_fill = 0;
	while (y_fill < game->win_height)
	{
		x_fill = 0;
		while (x_fill < game->win_width)
		{
			if (y_fill < game->win_height / 2)
				my_mlx_pixel_put_to_image(game, x_fill, y_fill,
					(int)rgb_to_int(game->config.ceiling_color));
			else
				my_mlx_pixel_put_to_image(game, x_fill, y_fill,
					(int)rgb_to_int(game->config.floor_color));
			x_fill++;
		}
		y_fill++;
	}
}

static int	verify_struct(t_game *game)
{
	if (!game || !game->mlx || !game->mlx_w
		|| !game->screen_image.img_ptr || !game->screen_image.addr)
	{
		ft_putstr_fd("Error:\n Game structure is not properly initialized.\n", 2);
		return (0);
	}
	if (!game->config.map || game->config.map_width <= 0
		|| game->config.map_height <= 0)
	{
		ft_putstr_fd("Error:\n Invalid map configuration.\n", 2);
		return (0);
	}
	return (1);
}

void	render_next_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	if (!verify_struct(game))
		return ;
	x = 0;
	fill_background(game);
	while (x < game->win_width)
	{
		init_ray_values(game, x, &ray);
		if (ray.map_x >= 0 && ray.map_x < game->config.map_width
			&& ray.map_y >= 0 && ray.map_y < game->config.map_height)
		{
			calculate_step_and_side_dist(game, &ray);
			perform_dda(game, &ray);
			calculate_wall_distance(game, &ray);
			draw_wall_line(game, &ray, x);
		}
		x++;
	}
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_w,
		game->screen_image.img_ptr, 0, 0);
}

