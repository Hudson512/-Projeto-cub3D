/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aux_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:18:45 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/25 14:44:40 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_skip_spaces(const char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == ',' || str[*i] == '\n' || str[*i] == '\0')
		return (0);
	return (1);
}

static int	ft_process_digit(int *res, char digit)
{
	if (*res > 25 || (*res == 25 && (digit - '0') > 5))
		return (0);
	*res = *res * 10 + (digit - '0');
	return (1);
}

static int	ft_check_next_char(const char *str, int *i, int *res)
{
	if (*res > 255 || *res < 0)
		return (0);
	if (str[*i] == ' ' || str[*i] == '\t')
	{
		(*i)++;
		return (1);
	}
	if (ft_isdigit(str[*i]))
		return (ft_process_digit(res, str[*i]));
	return (0);
}

int	ft_atoi_color(const char *nptr)
{
	char	*nbr;
	int		i;
	int		res;

	nbr = (char *)nptr;
	i = 0;
	res = 0;
	if (!ft_skip_spaces(nbr, &i))
		return (-1);
	while (nbr[i] && nbr[i] != ',' && nbr[i] != '\n')
	{
		if (!ft_check_next_char(nbr, &i, &res))
			return (-1);
		i++;
	}
	return (res);
}
