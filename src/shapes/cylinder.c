/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:58:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/16 09:58:47 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int ft_cylinder(t_rt *rt, t_vec3d coord, t_vec2d notnorm)
{
    t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -5.0f};
    t_vec3d rayOrigin = (t_vec3d){0.4f, 0.0f, rt->zoom};
    // rotate_z(&rayDirections, rt);

    float a = ((rayDirections.x * rayDirections.x) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x + rayOrigin.z * rayDirections.z);
    float c = -1.0f;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
        // (void)fulldir;
        t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        t_vec3d normal = hit_point;
        normalize(&normal);
        // update_light_dir(&rt->light_dir, rt->light_dir.x, rt->light_dir.y);
        t_vec3d ref_light_dir = rt->light_dir;
        normalize(&ref_light_dir);
        float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, 0xFF0000}));
        return (1);
    }
    else
        return (0);
}