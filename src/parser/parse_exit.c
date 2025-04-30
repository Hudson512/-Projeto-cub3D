/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:31:50 by hmateque          #+#    #+#             */
/*   Updated: 2025/04/29 10:32:09 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    parse_exit(char *msg)
{
    ft_putstr_fd(msg, 2);
    free_mem(get_mem_address());
    exit(1);
}