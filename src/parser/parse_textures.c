/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:13 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/12 15:38:57 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_strdup_texture(const char *s)
{
	char	*dest;
	size_t	len;
	int		i;

	while (*s == ' ' || *s == '\t')
		s++;
	len = ft_strlen(s);
	dest = ft_calloc(1, len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	capture_texture(char *line, t_config *config)
{
	char	*tmp;

	tmp = line;
	while (*tmp == ' ' || *tmp == '\t')
		tmp++;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		config->north_texture = ft_strdup_texture(tmp + 3);
		collect_mem(config->north_texture);
	}
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
	{
		config->south_texture = ft_strdup_texture(tmp + 3);
		collect_mem(config->south_texture);
	}
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
	{
		config->west_texture = ft_strdup_texture(tmp + 3);
		collect_mem(config->west_texture);
	}
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
	{
		config->east_texture = ft_strdup_texture(tmp + 3);
		collect_mem(config->east_texture);
	}
}
