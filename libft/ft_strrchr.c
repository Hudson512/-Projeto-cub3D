/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:12:35 by lantonio          #+#    #+#             */
/*   Updated: 2025/04/24 09:15:46 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			size;
	unsigned char	u;

	u = (unsigned char)c;
	size = ft_strlen(s);
	while (size + 1 > 0)
	{
		if (s[size] == u)
			return ((char *)&s[size]);
		size--;
	}
	return (0);
}
