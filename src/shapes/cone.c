/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:57:40 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 18:11:34 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cone(t_hitable *map, t_ray ray)
{
	t_vec3d vec = ray.dir;
	t_vec3d rayDirections = dir_from_mat(&camera()->mat, vec);
	t_vec3d rayOrigin = camera()->pos;

	float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
	float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
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
