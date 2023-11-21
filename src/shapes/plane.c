/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/21 21:58:42 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
float plane(t_map *map, t_vec3d dir, t_vec2d notnorm)
{
    (void)notnorm;
    // printf("rt->map->type= %d\n", map->type);
    // t_vec3d point_on_plane = (t_vec3d){0.0, 0.0, -10.0f}; // n
    // t_vec3d normal = (t_vec3d){0, 0, -1}; // p0
    // t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    // t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};

    t_vec3d point_on_plane = map->point; // n
    t_vec3d normal = map->normalized; // p0
    // t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, 1.0f}; // l0
    t_vec3d rayOrigin = camera()->pos;
	//t_vec3d rayOrigin = init_vec3d(0.0f, 0.0f, 1.0f);
    //t_vec3d l = ray;
    t_vec3d rayDirections = dir;
	//t_vec3d l = init_vec3d(coord.x, coord.y, -1.0f);
    // t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};

	float denom = dot(normal, rayDirections);
    //float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        t_vec3d p0l0 = t_vec3d_sub(point_on_plane, rayOrigin);
        float t = dot(p0l0, normal) / denom;
        if (t >= 0)
        {
            // printf("%f\n", t);
            return (t);
        }
    }
    return (__FLT_MAX__);
}
