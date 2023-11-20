/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:57:40 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/17 15:50:49 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// x - y = z * r
// float ft_cone(t_rt *rt, t_vec3d coord, t_vec2d notnorm)
float ft_cone(t_map *map, t_vec2d coord, t_vec2d notnorm)
{
    (void)map;
    (void)notnorm;
    // t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayDirections = dir_from_mat(camera()->mat, (t_vec3d){coord.x, coord.y, -1.0f});
    // rayDirections.x = coord.x;
    // rayDirections.y = coord.y;
    // rayDirections.z = -1.0f;

    // t_vec3d rayOrigin = (t_vec3d){-5.0f, 0.0f, 20.0};
    t_vec3d rayOrigin = camera()->pos;
    // rayOrigin.x = -5.0f;
    // rayOrigin.y = 0.0f;
    // rayOrigin.z = 20.0f;

    // rotate_z(&rayDirections, rt);

    float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
    float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
        if (nt > 0.0f)
        {
            return (nt);
            // t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
            // t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
            // t_vec3d normal = hit_point;
            // normalize(&normal);
            // t_vec3d ref_light_dir = rt->light_dir;
            // normalize(&ref_light_dir);
            // rotate_z(&ref_light_dir, rt);
            // float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
            // put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, 0xFF0000}));
        }
        return (__FLT_MAX__);
        // return (1);
    }
    else
        return (__FLT_MAX__);
}
