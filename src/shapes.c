
#include "minirt.h"

void rotate_x(vec3d *coord, t_rt *rt)
{
    float t_y = coord->y;

    coord->x = t_y * cos(rt->fTheta) + coord->z * sin(rt->fTheta);
    coord->z = t_y * -sin(rt->fTheta) + coord->z * cos(rt->fTheta);
}

void rotate_y(vec3d *coord, t_rt *rt)
{
    float t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->z*-sin(rt->fTheta);
    coord->z = t_x*sin(rt->fTheta) + coord->z*cos(rt->fTheta);
}

void rotate_z(vec3d *coord, t_rt *rt)
{
    float t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->y * sin(rt->fTheta);
    coord->y = t_x* -sin(rt->fTheta) + coord->y * cos(rt->fTheta);
}

int ft_cone(t_rt *rt, vec3d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    vec3d rayOrigin = (vec3d){0.4f, 0.0f, rt->zoom};
    rotate_z(&rayDirections, rt);

    float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
    float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        vec3d fulldir = vec3d_scale(rayDirections, nt);

        vec3d hit_point = vec3d_add(rayOrigin, vec3d_scale(rayDirections, nt));
        vec3d normal = hit_point;
        normalize(&normal);
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, 0xFF0000}));
    }
    else
        return (0);
}

int ft_sphere(t_rt *rt, vec2d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    vec3d rayOrigin = (vec3d){0.0f, 0.0f, rt->zoom};
    float radius = 0.5f;

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        vec3d fulldir = vec3d_scale(rayDirections, nt);

        vec3d hit_point = vec3d_add(rayOrigin, vec3d_scale(rayDirections, nt));
        vec3d normal = hit_point;
        normalize(&normal);
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, intensity}));
    }
    else if (ft_cone(rt, (vec3d){coord.x, coord.y, -1.0}, notnorm) == 0)
        return (0);
}