int ft_sphere(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayOrigin = rt->map->point;
    float radius = rt->map->diameter / 2;

    rayOrigin.x /= (float)SIZE;
    rayOrigin.y /= (float)SIZE;
    rayOrigin.x = rayOrigin.x * 2.0f - 1.0f;
    rayOrigin.y = rayOrigin.y * 2.0f - 1.0f;

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
        if (nt > 0.0f)
        {
        t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);

        t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        t_vec3d normal = hit_point;
        normalize(&normal);
        t_vec3d ref_light_dir = (t_vec3d){-1, -1, -1};
        normalize(&ref_light_dir);
        float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, intensity}));
        }
    }
    else if (ft_cone(rt, (t_vec3d){coord.x, coord.y, -1.0}, notnorm) == 0)
            return (0);
    return (1);
}