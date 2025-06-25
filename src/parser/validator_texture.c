/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:57:04 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 11:31:00 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}
	close(fd);
	return (1);
}

static int	validate_texture_img(void *mlx_ptr, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);
	if (!img)
	{
		ft_putstr_fd("Erro ao carregar a textura\n", 2);
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		return (0);
	}
	mlx_destroy_image(mlx_ptr, img);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (1);
}

static int	check_image(char *path)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		ft_putstr_fd("Erro ao inicializar o mlx\n", 2);
		return (0);
	}
	return (validate_texture_img(mlx, path));
}

int	is_texture_valid(char *texture)
{
	if (texture == NULL || texture[0] == '\0' || !check_extension(texture,
			".xpm") || !check_texture_path(texture) || !check_image(texture))
		return (0);
	return (1);
}
