/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/28 16:36:29 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float plane(t_map *map, t_vec3d dir)
{
    t_vec3d point_on_plane = map->point; // n
    t_vec3d normal = map->normalized; // p0
    t_vec3d rayOrigin = camera()->pos;
	float denom = dot(normal, dir);

    if (denom > 1e-6)
    {
        t_vec3d p0l0 = t_vec3d_sub(point_on_plane, rayOrigin);
        float t = dot(p0l0, normal) / denom;
        if (t >= 0)
            return (t);
    }
    return (__FLT_MAX__);
}
