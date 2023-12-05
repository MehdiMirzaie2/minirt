// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cylinder.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
// /*   Updated: 2023/12/04 14:27:44 by mmirzaie         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minirt.h"

// float	get_closert(t_vec2d hits, t_hitable *map, t_vec3d rayOrigin, t_ray ray)
// {
// 	float	nt_height;
// 	float	intersection_height;

// 	if (hits.t < hits.nt && hits.t > 0.001f)
// 	{
// 		intersection_height = rayOrigin.y + hits.t * ray.dir.y;
// 		if (intersection_height >= 0.001f && intersection_height <= map->height)
// 			return hits.t;
// 	}
// 	nt_height = rayOrigin.y + hits.nt * ray.dir.y;
// 	if (nt_height >= 0.0f && nt_height <= map->height)
// 		return hits.nt;
// 	return (__FLT_MAX__);
// }

// float ft_cylinder(t_hitable *map, t_ray ray)
// {
// 	float	rad;
// 	t_vec3d	quad;
// 	float	discriminant;
// 	t_vec2d	hits;
// 	t_vec3d rayOrigin;

// 	rayOrigin = t_vec3d_sub(ray.orig, map->point);
// 	rad = map->diameter / 2.0f;
// 	quad.aa = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
// 	quad.bb = 2.0f * (rayOrigin.x * ray.dir.x + rayOrigin.z * ray.dir.z);
// 	quad.cc = (rayOrigin.x * rayOrigin.x) + (rayOrigin.z * rayOrigin.z) - (rad * rad);
// 	discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
// 	if (discriminant >= 0.0f)
// 	{
// 		hits.t = (-quad.bb + sqrt(discriminant)) / (2.0f * quad.aa);
// 		hits.nt = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
// 		if (hits.nt > 0.001f)
// 			return (get_closert(hits, map, rayOrigin, ray));
// 	}
// 	return __FLT_MAX__;
// }


#include "minirt.h"

t_vec3d	transform_to_local(t_vec3d point, t_vec3d axis)
{
	t_vec3d local_point;
	// Perform the necessary transformations here based on the axis of orientation
	// For simplicity, assuming the cylinder's local y-axis is the axis of orientation
	local_point.x = point.x;
	local_point.y = cos(axis.y) * (point.y - axis.y) + sin(axis.y) * point.z;
	local_point.z = -sin(axis.y) * (point.y - axis.y) + cos(axis.y) * point.z;
	return local_point;
}

float get_closert(t_vec2d hits, t_hitable *map, t_vec3d rayOrigin, t_ray ray)
{
	float nt_height;
	float intersection_height;

	if (hits.t < hits.nt && hits.t > 0.001f)
	{
		intersection_height = rayOrigin.y + hits.t * ray.dir.y;
		if (intersection_height >= 0.001f && intersection_height <= map->height)
			return hits.t;
	}
	nt_height = rayOrigin.y + hits.nt * ray.dir.y;
	if (nt_height >= 0.0f && nt_height <= map->height)
		return hits.nt;
	return __FLT_MAX__;
}

float ft_cylinder(t_hitable *map, t_ray ray)
{
	float rad;
	t_vec3d quad;
	float discriminant;
	t_vec2d hits;
	t_vec3d rayOrigin;

	rayOrigin = transform_to_local(t_vec3d_sub(ray.orig, map->point), map->normalized);
	rad = map->diameter / 2.0f;
	quad.aa = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	quad.bb = 2.0f * (rayOrigin.x * ray.dir.x + rayOrigin.z * ray.dir.z);
	quad.cc = (rayOrigin.x * rayOrigin.x) + (rayOrigin.z * rayOrigin.z) - (rad * rad);
	discriminant = quad.bb * quad.bb - 4.0f * quad.aa * quad.cc;
	if (discriminant >= 0.0f)
	{
		hits.t = (-quad.bb + sqrt(discriminant)) / (2.0f * quad.aa);
		hits.nt = (-quad.bb - sqrt(discriminant)) / (2.0f * quad.aa);
		if (hits.nt > 0.001f)
			return get_closert(hits, map, rayOrigin, ray);
	}
	return __FLT_MAX__;
}
