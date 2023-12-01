/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 18:11:43 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
float plane(t_hitable *map, t_ray ray)
{
	float	denom;

	denom = dot(map->normalized, ray.dir);
	if (denom > 1e-6)
	{
		t_vec3d p0l0 = t_vec3d_sub(map->normalized, camera()->pos);
		float t = dot(p0l0, map->point) / denom;
		if (t > 0)
			return (t);
	}
	return (__FLT_MAX__);
}

float shadow_plane(t_hitable *map, t_ray ray)
{
	float	denom;

	denom = dot(map->normalized, ray.dir);
	if (denom > 1e-6)
	{
		t_vec3d p0l0 = t_vec3d_sub(map->normalized, ray.orig);
		float t = dot(p0l0, map->point) / denom;
		if (t > 0)
			return (t);
	}
	return (__FLT_MAX__);
}
