/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_pixal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:36:39 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/05 15:34:15 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpayload	miss(const t_ray ray)
{
	t_hitpayload	payload;

	(void)ray;
	payload.hit_distance = -1.0f;
	return (payload);
}

t_hitpayload	closest_hit(const t_ray ray, float hit_distance, t_hitable *obj)
{
	t_hitpayload	payload;
	t_vec3d			origin;

	origin = t_vec3d_sub(ray.orig, obj->point);
	payload.raydir = t_vec3d_scale(ray.dir, hit_distance);
	payload.hit_distance = hit_distance;
	payload.obj = obj;
	payload.world_positoin = t_vec3d_add(origin, payload.raydir);
	payload.world_normal = payload.world_positoin;
	normalize(&payload.world_normal);
	payload.world_positoin = t_vec3d_add(payload.world_positoin, obj->point);
	return (payload);
}

float	trace_ray_helper(t_hitable *ref_map, t_ray ray)
{
	if (ref_map->type == SP)
		return (ft_sphere(ref_map, ray));
	else if (ref_map->type == CY)
		return (ft_cylinder(ref_map, ray));
	else if (ref_map->type == PL)
		return (plane(ref_map, ray));
	else if (ref_map->type == CN)
		return (ft_cone(ref_map, ray));
	return (0.0f);
}

t_hitpayload	trace_ray(t_hitable *map, t_ray ray)
{
	t_hitable	*ref_map;
	t_hitable	*closest_obj;
	float		closest_t_val;
	float		old_closest;

	ref_map = map;
	closest_obj = NULL;
	old_closest = __FLT_MAX__;
	while (ref_map)
	{
		closest_t_val = trace_ray_helper(ref_map, ray);
		if (closest_t_val < old_closest)
		{
			old_closest = closest_t_val;
			closest_obj = ref_map;
		}
		ref_map = ref_map->next;
	}
	if (closest_obj == NULL)
		return (miss(ray));
	return (closest_hit(ray, old_closest, closest_obj));
}

t_vec3d	per_pixal(t_rt *rt, uint32_t x, uint32_t y)
{
	t_ray			ray;
	t_vec3d			fcol;
	t_hitpayload	payload;

	ray = set_ray(x, y);
	fcol = rt->mincolour;
	rt->mul = 1.0f;
	rt->i = -1;
	while (++(rt->i) < 5)
	{
		payload = trace_ray(rt->hitable, ray);
		if (payload.hit_distance < 0.0f)
		{
			fcol = (t_vec3d_add(fcol, t_vec3d_scale(rt->mincolour, rt->mul)));
			break ;
		}
		fcol = t_vec3d_add(fcol, t_vec3d_scale(color_multiply(payload.obj->rgb,
						set_light_ratio(rt, &payload)), rt->mul));
		rt->mul *= 0.5f;
		ray.orig = t_vec3d_add(payload.world_positoin,
				t_vec3d_scale(payload.world_normal, 0.0001f));
		ray.dir = reflect(ray.dir, t_vec3d_add(payload.world_normal,
					getrendomvec3d(payload.obj->roughness)));
	}
	return (fcol);
}
