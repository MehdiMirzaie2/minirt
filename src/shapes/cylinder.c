/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 13:47:36 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cylinder(t_map *map, t_ray ray)
{
	float	rad;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	float	nt;
	float	nt_height;
	float	intersection_height;

	rad = map->diameter / 2.0f;
	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	b = 2.0f * (ray.orig.x * ray.dir.x + ray.orig.z * ray.dir.z);
	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - (rad * rad);
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		t = (-b + sqrt(discriminant)) / (2.0f * a);
		nt = (-b - sqrt(discriminant)) / (2.0f * a);

		if (nt > 0.001f)
		{
			if (t < nt && t > 0.001f)

				intersection_height = ray.orig.y + t * ray.dir.y;

				// Check if the intersection height is within the
				if (intersection_height >= 0.0f && intersection_height <= map->height)
					return t;

			nt_height = ray.orig.y + nt * ray.dir.y;
			// Check if the intersection height is within the limits
			if (nt_height >= 0.0f && nt_height <= map->height)
				return nt;
		}
	}
	return __FLT_MAX__;
}
