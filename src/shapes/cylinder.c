/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/30 17:04:50 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cylinder(t_hitable *map, t_ray ray)
{
    const float radius = map->diameter / 2.0f;
    float a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
    float b = 2.0f * (ray.orig.x * ray.dir.x + ray.orig.z * ray.dir.z);
    float c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - (radius * radius);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        if (nt > 0.001f)
        {
            if (t < nt && t > 0.001f)
            {
                float intersection_height = ray.orig.y + t * ray.dir.y;

                // Check if the intersection height is within the limits
                if (intersection_height >= 0.0f && intersection_height <= map->height)
                    return t;
            }

            float nt_height = ray.orig.y + nt * ray.dir.y;

            // Check if the intersection height is within the limits
            if (nt_height >= 0.0f && nt_height <= map->height)
                return nt;
        }
    }
    return __FLT_MAX__;
}
