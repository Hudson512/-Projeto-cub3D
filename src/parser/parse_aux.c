/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:49:18 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 14:18:04 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup_texture(const char *s)
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

int	check_digit_count(char *line, int start)
{
	int	count;
	int	i;

	i = start;
	count = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) != 1)
		return (-1);
	while (line[i] && ft_isdigit(line[i]))
	{
		count++;
		i++;
	}
	if (count <= 3)
		return (count);
	return (-1);
}

int	is_digit_string(char *line)
{
	int	i;
	int	cont_digits;

	i = 0;
	cont_digits = 0;
	while (line[i] && line[i] != ',' && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		if (ft_isdigit(line[i]))
			cont_digits++;
		i++;
	}
	if (i == 0 || !(cont_digits >= 0 && cont_digits <= 3))
		return (0);
	return (1);
}


