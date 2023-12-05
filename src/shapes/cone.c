/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:57:40 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 11:19:17 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cone(t_hitable *map, t_ray ray)
{
	// t_vec3d vec = ray.dir;
	// t_vec3d rayDirections = dir_from_mat(&camera()->mat, vec);
	t_vec3d rayOrigin = t_vec3d_sub(ray.orig, map->point);

	float a = ((ray.dir.x * ray.dir.x) - (ray.dir.y * ray.dir.y) + (ray.dir.z * ray.dir.z));
	float b = 2.0f * (rayOrigin.x * ray.dir.x - rayOrigin.y * ray.dir.y + rayOrigin.z * ray.dir.z);
	float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		float t = (-b + sqrt(discriminant)) / (2.0f * a);
		(void)t;
		float nt = (-b - sqrt(discriminant)) / (2.0f * a);
		if (nt > 0.0f)
			return (nt);
	}
	return (__FLT_MAX__);
}
