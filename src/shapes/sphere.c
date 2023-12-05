/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/04 11:47:06 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_sphere(t_hitable *map, t_ray ray)
{
	t_vec3d	rayOrigin;
	float	radius;
	float	close_t;
	t_vec3d	quad;
	float	discriminant;

	rayOrigin = t_vec3d_sub(ray.orig, map->point);
	radius = map->diameter / 2.0f;
	quad.aa = dot(ray.dir, ray.dir);
	quad.bb = 2.0f * dot(rayOrigin, ray.dir);
	quad.cc = dot(rayOrigin, rayOrigin) - (radius * radius);
	discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
	if (discriminant >= 0.0f)
	{
		close_t = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
		if (close_t > 0.001)
			return (close_t);
	}
	return (__FLT_MAX__);
}
