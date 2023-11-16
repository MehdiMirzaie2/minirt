/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/16 14:50:44 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    t_vec3d normal = (t_vec3d){1, 0, 0}; // p0
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


    // t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    // t_vec3d normal = rt->map->normalized; // p0
    // t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    // t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};

    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        // t_vec3d p0l0 = normal - rayOrigin;
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        return (t);
        // return (t >= 0);
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0xf9f1f0);
    }
    return (__FLT_MAX__);
}