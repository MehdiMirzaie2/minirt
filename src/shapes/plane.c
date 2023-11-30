/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/24 11:15:03 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
float plane(t_map *map, t_ray ray)
{
    t_vec3d point_on_plane = map->point; // n
    t_vec3d normal = map->normalized; // p0
    t_vec3d rayOrigin = init_vec3d(0.0f, 0.0f, 1.0f);
    t_vec3d l = ray.dir;

    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        if (t > 0)
            return (t);
    }
    return (__FLT_MAX__);
}