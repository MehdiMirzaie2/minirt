/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/28 22:58:55 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float ft_cylinder(t_map *map, t_vec3d dir)
{
    t_vec3d rayDirections = dir;
	//t_vec3d rayDirections = init_vec3d(coord.x, coord.y, -1.0f);
    // t_vec3d rayOrigin = (t_vec3d){0.4f, 0.0f, 1.0};
    t_vec3d rayOrigin = t_vec3d_sub(camera()->pos, map->point);
    // rotate_z(&rayDirections, rt);
	float	radius = map->diameter / 2.0f;

    //float a = ((rayDirections.x * rayDirections.x) + (rayDirections.z * rayDirections.z));
    //float b = 2.0f * (rayOrigin.x * rayDirections.x + rayOrigin.z * rayDirections.z);
    //float c = -1.0f;

	float	a = dot(rayDirections, rayDirections) - pow(dot(rayDirections, map->normalized), 2);
	float	b = 2 * (dot(rayDirections, rayOrigin) - dot(rayDirections, map->normalized) \
		* dot(rayOrigin, map->normalized));
	float	c = dot(rayOrigin, rayOrigin) - pow(dot(rayOrigin, map->normalized), 2) - pow(radius, 2);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float	t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float	nt = (-b - sqrt(discriminant)) / (2.0f * a);
		//float	half_height = map->height / 2.0f;
		//t_vec3d	point1 =
        return (nt);
    }
    else
        return (__FLT_MAX__);
}
