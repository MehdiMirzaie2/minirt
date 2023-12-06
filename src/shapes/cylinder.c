/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:40:34 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/06 10:43:51 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec3d	transform_to_local(t_vec3d point, t_vec3d axis)
// {
// 	t_vec3d	local_point;

// 	local_point.x = point.x;
// 	local_point.y = cos(axis.y) * (point.y - axis.y) + sin(axis.y) * point.z;
// 	local_point.z = -sin(axis.y) * (point.y - axis.y) + cos(axis.y) * point.z;
// 	return (local_point);
// }

	// float	nt_height;
	// float	intersection_height;

	// nt_height = rayorigin.y + hits.nt * ray.dir.y;
	// if (nt_height >= 0.0f && nt_height <= map->height)
	// 	return (hits.nt);
	// if (hits.t > hits.nt && hits.t > 0.001f)
	// {
	// 	intersection_height = rayorigin.y + hits.t * ray.dir.y;
	// 	if (intersection_height >= 0.001f && intersection_height <= map->height)
	// 		return (hits.t);
	// }
	// return (__FLT_MAX__);

float	get_closert(t_vec2d hits, t_hitable *map, t_vec3d rayorigin, t_ray ray)
{
	t_vec3d	p1;
	t_vec3d	p2;
	float	y1;
	float	y2;

	p1 = t_vec3d_add(rayorigin, t_vec3d_scale(ray.dir, hits.nt));
	y1 = p1.y - map->point.y;
	if (y1 < -map->height / 2.0f || y1 > map->height / 2.0f)
		hits.nt = __FLT_MAX__;
	else
		return (hits.nt);
	p2 = t_vec3d_add(rayorigin, t_vec3d_scale(ray.dir, hits.t));
	y2 = p2.y - map->point.y;
	if (y2 < -map->height / 2.0f || y2 > map->height / 2.0f)
		hits.t = __FLT_MAX__;
	else
		return (hits.t);
	return (__FLT_MAX__);
}

float	ft_cylinder(t_hitable *map, t_ray ray)
{
	t_vec3d		quad;
	float		discriminant;
	t_vec2d		hits;
	t_vec3d		rayorigin;

	rayorigin = t_vec3d_sub(ray.orig, map->point);
	quad.aa = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	quad.bb = 2.0f * (rayorigin.x * ray.dir.x + rayorigin.z * ray.dir.z);
	quad.cc = (rayorigin.x * rayorigin.x) + (rayorigin.z * rayorigin.z)
		- (map->radius2);
	discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
	if (discriminant >= 0.0f)
	{
		hits.t = (-quad.bb + sqrt(discriminant)) / (2.0f * quad.aa);
		hits.nt = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
		if (hits.nt > 0.001f)
			return (get_closert(hits, map, rayorigin, ray));
	}
	return (__FLT_MAX__);
}
