#include "minirt.h"

t_light	*light(void)
{
	static t_light	light;

	return (&light);
}

void	set_light(t_map map)
{
	light()->pos.x = map.point.x;
	light()->pos.y = map.point.y;
	light()->pos.z = map.point.z;
	light()->intensity = map.brightness;
	light()->color.r = map.rgb.r;
	light()->color.g = map.rgb.g;
	light()->color.b = map.rgb.b;
}

t_vec3d	color_multiply(t_vec3d color, float ratio)
{
	t_vec3d	result;

	result = init_vec3d(color.r * ratio, color.g * ratio, color.b * ratio);
	if (result.r > 255)
		result.r = 255;
	if (result.r < 0)
		result.r = 0;
	if (result.g > 255)
		result.g = 255;
	if (result.g < 0)
		result.g = 0;
	if (result.b > 255)
		result.b = 255;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

float	diffuse_light(t_vec3d norm, t_vec3d lvec)
{
	float	result;
	float	n_l_dot;

	result = a_light()->intensity;
	n_l_dot = dot(norm, lvec);
	if (n_l_dot > 0)
		result += n_l_dot / (length(norm) * length(lvec));
	return (result);
}

float	specular_light(t_vec3d norm, t_vec3d lvec, t_vec3d dir, float ratio)
{
	float	result;
	float	l_d_dot;
	t_vec3d	norm_double;
	t_vec3d	temp;
	t_vec3d	r;
	int		spec;

	result = ratio;
	spec = 25;
	norm_double = t_vec3d_scale(norm, 2);
	temp = t_vec3d_scale(norm_double, dot(norm, lvec));
	r = t_vec3d_sub(temp, lvec);
	l_d_dot = dot(r, dir);
	if (l_d_dot > 0.0f)
		result += light()->intensity * pow(l_d_dot / (length(r) * length(dir)), spec);
	return (result);
}
