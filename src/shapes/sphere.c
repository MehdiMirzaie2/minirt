/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/16 12:41:35 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int ft_sphere(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom};
    // t_vec3d rayOrigin = (t_vec3d){0.0, rt->camera.y, rt->zoom};
    float radius = 0.5f;

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);

        t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        t_vec3d normal = hit_point;
        normalize(&normal);
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, t_vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, intensity}));
    }
    else
        return (0);
}