/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 13:37:47 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	plane(t_hitable *map, t_ray ray)
{
	float	denom;
	t_vec3d	p0l0;
	float	t;

	denom = dot(map->normalized, ray.dir);
	if (denom > 1e-6)
	{
		p0l0 = t_vec3d_sub(map->normalized, camera()->pos);
		t = dot(p0l0, map->point) / denom;
		if (t > 0)
			return (t);
	}
	return (__FLT_MAX__);
}
