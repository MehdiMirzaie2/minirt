/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3d_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:44:51 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 14:45:01 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	t_vec3dmemset(t_vec3d accum[][SIZE*SIZE], int c)
{
	size_t			x;
	size_t			y;
	unsigned char	chr;

	chr = c;
	y = -1;
	while (++y < SIZE)
	{
		x = -1;
		while (++x < SIZE)
		{
			accum[0][x + y * SIZE].y = chr;
			accum[0][x + y * SIZE].z = chr;
			accum[0][x + y * SIZE].x = chr;
		}
	}
}