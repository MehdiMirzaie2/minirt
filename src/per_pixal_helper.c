/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_pixal_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:33:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/05 15:34:18 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Reflection=Incident−2×(Normal⋅Incident)×Normal
t_vec3d	reflect(t_vec3d incident, t_vec3d normal)
{
	return (t_vec3d_sub(incident, \
		t_vec3d_scale(normal, 2.0f * dot(incident, normal))));
}

t_vec3d	getrendomvec3d(float roughness)
{
	t_vec3d	ran_vec;

	ran_vec.x = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.y = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.z = ((float)rand() / RAND_MAX - 0.5) * roughness;
	return (ran_vec);
}

void	set_raydir(t_vec3d *raydir)
{
	t_vec2d	ndc_space;
	t_vec2d	screen_space;
	t_vec2d	camera_space;
	float	ar;

	ar = SIZE / SIZE;
	ndc_space.x = ((raydir->x + 0.5f) / SIZE);
	ndc_space.y = ((raydir->y + 0.5f) / SIZE);
	screen_space.x = 2 * ndc_space.x - 1;
	screen_space.y = 2 * ndc_space.y - 1;
	screen_space.y = 1 - 2 * ndc_space.y;
	camera_space.x = (2 * screen_space.x - 1) * ar
		* (1 / tan(camera()->fov / 2));
	camera_space.y = (1 - 2 * screen_space.y) * (1 / tan(camera()->fov / 2));
	raydir->x = camera_space.x;
	raydir->y = camera_space.y;
}

t_ray	set_ray(uint32_t x, uint32_t y)
{
	t_ray	ray;

	ray.orig = camera()->pos;
	ray.dir = init_vec3d((float)x, (float)y, -1.0f);
	set_raydir(&ray.dir);
	ray.dir = dir_from_mat(&camera()->mat, ray.dir);
	normalize(&ray.dir);
	return (ray);
}
