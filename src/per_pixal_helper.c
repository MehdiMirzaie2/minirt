/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_pixal_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:33:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/06 09:16:41 by jaeshin          ###   ########.fr       */
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
	float	tangent;

	tangent = tan(camera()->fov / 2 * M_PI / 180);
	raydir->x = (2 * ((raydir->x + 0.5) / SIZE) - 1) * tangent;
	raydir->y = -(1 - 2 * ((raydir->y + 0.5) / SIZE) * tangent);
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
