/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:00:34 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/06 11:15:56 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < l)
	{
		dest[i] = src[i];
		i++;
	}
	if (l)
		dest[i] = '\0';
	return (ft_strlen(src));
}
