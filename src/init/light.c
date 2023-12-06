/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:38:18 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/06 09:56:54 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d	color_multiply(t_vec3d color, float ratio)
{
	t_vec3d	result;

	result = init_vec3d(color.r * ratio, color.g * ratio, color.b * ratio);
	if (result.r > 255)
		result.r = 255;
	if (result.r < 0)
		result.r = 0;
	if (result.g > 255)
		result.g = 255;
	if (result.g < 0)
		result.g = 0;
	if (result.b > 255)
		result.b = 255;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

float	diffuse_light(t_vec3d norm, t_vec3d lvec)
{
	float	result;
	float	n_l_dot;

	result = a_light()->intensity;
	n_l_dot = dot(norm, lvec);
	if (n_l_dot > 0)
		result += n_l_dot / (length(norm) * length(lvec));
	return (result);
}

float	specular_light(t_vec3d norm, t_vec3d lvec, t_vec3d dir, float ratio)
{
	float	result;
	float	l_d_dot;
	t_vec3d	norm_double;
	t_vec3d	temp;
	t_vec3d	r;

	result = ratio;
	norm_double = t_vec3d_scale(norm, 2);
	temp = t_vec3d_scale(norm_double, dot(norm, lvec));
	r = t_vec3d_sub(temp, lvec);
	l_d_dot = dot(r, dir);
	if (l_d_dot > 0.0f)
		result += light()->intensity * \
			pow(l_d_dot / (length(r) * length(dir)), 10);
	return (result);
}

float	set_light_ratio(t_rt *rt, t_hitpayload *payload)
{
	float			light_ratio;
	t_vec3d			hit_point;
	t_vec3d			normal;
	t_vec3d			lvec;
	t_hitpayload	shadow_check;

	light_ratio = 0.0f;
	hit_point = t_vec3d_add(camera()->pos, payload->raydir);
	normal = t_vec3d_sub(hit_point, payload->obj->point);
	lvec = t_vec3d_sub(light()->pos, hit_point);
	shadow_check = trace_ray(rt->hitable, (t_ray){hit_point, lvec});
	if (payload->obj->type == PL && shadow_check.hit_distance == -1.0f)
		light_ratio = a_light()->intensity;
	else if (shadow_check.hit_distance == -1.0f)
	{
		light_ratio = diffuse_light(normal, lvec);
		light_ratio = specular_light(normal, lvec, \
			t_vec3d_scale(payload->raydir, -1), light_ratio);
	}
	return (light_ratio);
}
