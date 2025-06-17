/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:49:18 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/17 10:30:27 by hmateque         ###   ########.fr       */
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

	i = 0;
	while (line[i] && line[i] != ',' && line[i] != '\n' && i < 3)
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		i++;
	}
	if (i == 0 || i > 3)
		return (0);
	return (1);
}

int	ft_atoi_color(const char *nptr)
{
	char	*nbr;
	int		i;
	int		sign;
	int		res;

	nbr = (char *)nptr;
	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	while (nbr[i])
	{
		if (nbr[i] == ' ')
		{
			i++;
			continue ;
		}
		if (ft_isdigit(nbr[i]))
			res = res * 10 + (nbr[i] - '0');
		else
			break ;
		i++;
	}
	return (res * sign);
}
