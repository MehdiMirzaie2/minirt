/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 18:11:48 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_sphere(t_hitable *map, t_ray ray)
{
	t_vec3d	rayOrigin;
	float	radius;
	float	close_t;
	t_vec3d	quad;

	rayOrigin = t_vec3d_sub(ray.orig, map->point);
	radius = map->diameter / 2.0f;
	quad.aa = dot(ray.dir, ray.dir);
	quad.bb = 2.0f * dot(rayOrigin, ray.dir);
	quad.cc = dot(rayOrigin, rayOrigin) - (radius * radius);
	float discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
	if (discriminant >= 0.0f)
	{
		// float t = (-quad.b + sqrt(discriminant)) / (2.0f * quad.a);
		// (void)t;
		close_t = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
		if (close_t > 0.001)
			return (close_t);
	}
	return (__FLT_MAX__);
}
