/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:57:40 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 13:46:45 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_cone(t_hitable *map, t_ray ray)
{
	t_vec3d	rayorigin;
	t_vec3d	quad;
	t_vec2d	tees;
	float	discriminant;

	rayorigin = t_vec3d_sub(ray.orig, map->point);
	quad.aa = ((ray.dir.x * ray.dir.x) - (ray.dir.y * ray.dir.y)
			+ (ray.dir.z * ray.dir.z));
	quad.bb = 2.0f * (rayorigin.x * ray.dir.x - rayorigin.y * ray.dir.y
			+ rayorigin.z * ray.dir.z);
	quad.cc = ((rayorigin.x * rayorigin.x) - (rayorigin.y * rayorigin.y)
			+ (rayorigin.z * rayorigin.z));
	discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
	if (discriminant >= 0.0f)
	{
		tees.t = (-quad.bb + sqrt(discriminant)) / (2.0f * quad.aa);
		(void)tees.t;
		tees.nt = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
		if (tees.nt > 0.0f)
			return (tees.nt);
	}
	return (__FLT_MAX__);
}
