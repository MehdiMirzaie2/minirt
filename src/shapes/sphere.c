/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/23 15:50:39 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_sphere(t_map *map, t_ray ray)
{
    t_vec3d rayOrigin = map->point;
    const float radius = map->diameter / 2.0f;

    float a = dot(ray.dir, ray.dir);
    float b = 2.0f * dot(rayOrigin, ray.dir);
    float c = dot(rayOrigin, rayOrigin) - (radius * radius);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
        return (nt);
    }
    else
        return (__FLT_MAX__);
}
