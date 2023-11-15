
#include "minirt.h"

void rotate_x(t_vec3 *coord, t_rt *rt)
{
    float	t_y = coord->y;

    coord->x = t_y * cos(rt->fTheta) + coord->z * sin(rt->fTheta);
    coord->z = t_y * -sin(rt->fTheta) + coord->z * cos(rt->fTheta);
}

void rotate_y(t_vec3 *coord, t_rt *rt)
{
    float	t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->z*-sin(rt->fTheta);
    coord->z = t_x*sin(rt->fTheta) + coord->z*cos(rt->fTheta);
}

void rotate_z(t_vec3 *coord, t_rt *rt)
{
    float	t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->y * sin(rt->fTheta);
    coord->y = t_x* -sin(rt->fTheta) + coord->y * cos(rt->fTheta);
}

int ft_cone(t_rt *rt, t_vec3 coord, t_vec2 notnorm)
{
	camera()->dir.x = coord.x;
	camera()->dir.y = coord.y;
	camera()->dir.z = -1.0f;
    t_vec3 rayDirections = camera()->dir;
	camera()->pos.z = rt->zoom;
    t_vec3 rayOrigin = camera()->pos;
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
    	normal = vec3_normalized(normal);
        rt->light_dir = vec3_normalized(rt->light_dir);
        float intensity = max(vec3_dot(normal, vec3_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_color){intensity, intensity, 0xFF0000}));
    }
    else
        return (0);
}

int ft_sphere(t_rt *rt, t_vec2 coord, t_vec2 notnorm)
{
	camera()->dir.x = coord.x;
	camera()->dir.y = coord.y;
	camera()->dir.z = -1.0f;
	camera()->pos.z = rt->zoom;
	t_vec3 rayDirections = camera()->dir;
    t_vec3 rayOrigin = camera()->pos;
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

		normal = vec3_normalized(normal);
		rt->light_dir = vec3_normalized(rt->light_dir);
		float intensity = max(vec3_dot(normal, vec3_scale(rt->light_dir, -1)), 0.0);

		put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_color){intensity, intensity, intensity}));
	}
	else if (ft_cone(rt, (t_vec3){coord.x, coord.y, -1.0}, notnorm) == 0)
		return (0);
}
