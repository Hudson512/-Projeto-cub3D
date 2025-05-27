/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:43:34 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/27 10:46:31 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int rgb_to_int(t_color color)
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}

void update_ray_x(t_ray *ray)
{
    ray->side_dist_x += ray->delta_dist_x;
    ray->map_x += ray->step_x;
    ray->side = 0;
}

void update_ray_y(t_ray *ray)
{
    ray->side_dist_y += ray->delta_dist_y;
    ray->map_y += ray->step_y;
    ray->side = 1;
}

int is_wall_hit(t_game *game, t_ray *ray)
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

static void	init_ray_values(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->config.player_x;
	ray->map_y = (int)game->config.player_y;
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->side = 0;
}

static void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
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

static void	perform_dda(t_game *game, t_ray *ray)
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

static void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)((game->win_height / ray->perp_wall_dist) * game->fov_scale_factor);
	draw_start = -line_height / 2 + game->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->win_height / 2;
	if (draw_end >= game->win_height)
		draw_end = game->win_height - 1;
	color = (ray->side == 1) ? 0x00707070 : 0x00909090;
	y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put_to_image(game, x, y, color);
		y++;
	}
}

void calculate_wall_distance(t_game *game, t_ray *ray)
{
    (void)game; // Suppress unused parameter warning
    if (ray->side == 0)
        ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
    if (ray->perp_wall_dist <= 0.0001)
        ray->perp_wall_dist = 0.0001;
}

void	render_next_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	if (!verify_struct(game))
		return ;
	fill_background(game);
	x = 0;
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

int	verify_struct(t_game *game)
{
	if (!game || !game->mlx || !game->mlx_w
		|| !game->screen_image.img_ptr || !game->screen_image.addr)
	{
		ft_putstr_fd("Error: Game structure is not properly initialized.\n", 2);
		return (0);
	}
	if (!game->config.map || game->config.map_width <= 0
		|| game->config.map_height <= 0)
	{
		ft_putstr_fd("Error: Invalid map configuration.\n", 2);
		return (0);
	}
	return (1);
}
