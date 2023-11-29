/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/27 12:48:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_sphere(t_map *map, t_vec3d dir)
{
    t_vec3d rayDirections = dir;
    t_vec3d rayOrigin = t_vec3d_sub(camera()->pos, map->point);
    float radius = map->diameter / 2.0f;

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
		(void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
		if (nt >= 0.001 || nt <= __FLT_MAX__)
			return (nt);
		//else if (t >= 0.001 || t <= __FLT_MAX__)
		//	return (t);
    }
        return (__FLT_MAX__);
}
