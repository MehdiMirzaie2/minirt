/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/23 15:45:23 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cylinder(t_map *map, t_ray ray)
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
        if (nt >= 0)
        {
            if (t < nt && t >= 0)
                return (t);
            return (nt);
        }
    }
    return (__FLT_MAX__);
}
