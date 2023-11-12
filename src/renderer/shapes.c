
#include "minirt.h"

void rotate_x(t_vec3 *coord, t_rt *rt)
{
    float	t_y = coord->y;
	float	fTheta = 2.0f;

    coord->x = t_y * cos(fTheta) + coord->z * sin(fTheta);
    coord->z = t_y * -sin(fTheta) + coord->z * cos(fTheta);
}

void rotate_y(t_vec3 *coord, t_rt *rt)
{
    float	t_x = coord->x;
	float	fTheta = 2.0f;

    coord->x = t_x*cos(fTheta) + coord->z*-sin(fTheta);
    coord->z = t_x*sin(fTheta) + coord->z*cos(fTheta);
}

void rotate_z(t_vec3 *coord, t_rt *rt)
{
    float	t_x = coord->x;
	float	fTheta = 2.0f;

    coord->x = t_x*cos(fTheta) + coord->y * sin(fTheta);
    coord->y = t_x* -sin(fTheta) + coord->y * cos(fTheta);
}

int ft_cone(t_rt *rt, t_vec3 coord, t_vec2 notnorm)
{
    t_vec3 rayDirections = (t_vec3){coord.x, coord.y, -1.0f};
    t_vec3 rayOrigin = (t_vec3){0.4f, 0.0f, rt->zoom};
    rotate_z(&rayDirections, rt);

    float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
    float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        t_vec3 fulldir = vec3_scale(rayDirections, nt);

        t_vec3 hit_point = vec3_add(rayOrigin, vec3_scale(rayDirections, nt));
        t_vec3 normal = hit_point;
    	vec3_normalize(normal);
        vec3_normalize(rt->light_dir);
        float intensity = max(vec3_dot(normal, vec3_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3){intensity, intensity, 0xFF0000}));
    }
    else
        return (0);
}

int ft_sphere(t_rt *rt, t_vec2 coord, t_vec2 notnorm)
{
    t_vec3 rayDirections = (t_vec3){coord.x, coord.y, -1.0f};
    t_vec3 rayOrigin = (t_vec3){0.0f, 0.0f, rt->zoom};
    float radius = 0.5f;

    float a = vec3_dot(rayDirections, rayDirections);
    float b = 2.0f * vec3_dot(rayOrigin, rayDirections);
    float c = vec3_dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        t_vec3 fulldir = vec3_scale(rayDirections, nt);

        t_vec3 hit_point = vec3_add(rayOrigin, vec3_scale(rayDirections, nt));
        t_vec3 normal = hit_point;
        vec3_normalize(normal);
        vec3_normalize(rt->light_dir);
        float intensity = max(vec3_dot(normal, vec3_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3){intensity, intensity, intensity}));
    }
    else if (ft_cone(rt, (t_vec3){coord.x, coord.y, -1.0}, notnorm) == 0)
        return (0);
}
