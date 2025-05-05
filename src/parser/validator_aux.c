/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:51:16 by hmateque          #+#    #+#             */
/*   Updated: 2025/05/05 09:08:04 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(const char *filename, char *str_ext)
{
	size_t	str_len;
	size_t	suffix_len;

	str_len = ft_strlen(filename);
	suffix_len = ft_strlen(str_ext);
	if (suffix_len > str_len)
		return (0);
	return (ft_strncmp(filename + str_len - suffix_len,
			str_ext, suffix_len) == 0);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
