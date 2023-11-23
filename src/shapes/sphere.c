/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/23 11:59:31 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float ft_sphere(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
float ft_sphere(t_map *map, t_vec3d dir, t_vec2d notnorm)
{
    (void)notnorm;
    // t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayDirections = dir;
	//t_vec3d rayDirections = init_vec3d(coord.x, coord.y, -1.0f);
    // t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom};
    t_vec3d rayOrigin = camera()->pos;
    float radius = map->diameter / 2.0f;
    // float radius = 0.5f;
    // printf("%f\n", rt->map->diameter);

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(t_vec3d_sub(rayOrigin, map->point), rayDirections);
    float c = dot(t_vec3d_sub(rayOrigin, map->point), t_vec3d_sub(rayOrigin, map->point)) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    // printf("%f\n", discriminant);
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;

        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
		if (nt >= 0)
			return (nt);
		//(void)nt;
        // printf("\n%f\n", nt);
        // t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);

        // t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        // t_vec3d normal = hit_point;
        // normalize(&normal);
        // normalize(&rt->light_dir);
        // float intensity = max(dot(normal, t_vec3d_scale(rt->light_dir, -1)), 0.0);
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, intensity}));
    }
        return (__FLT_MAX__);
}
