/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:59:59 by hmateque          #+#    #+#             */
/*   Updated: 2025/06/11 14:54:16 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_color_valid(t_color color)
{
	if (color.r == -1 || color.g == -1 || color.b == -1)
		return (0);
	if ((color.r < 0 || color.r > 255) || (color.g < 0 || color.g > 255)
		|| (color.b < 0 || color.b > 255))
		return (0);
	return (1);
}
