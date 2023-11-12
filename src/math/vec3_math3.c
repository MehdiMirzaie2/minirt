#include "minirt.h"

float	vec3_magnitude(t_vec3 v)
{
	float	magnitude;

	magnitude = sqrt(\
		pow(v.x, 2) + \
		pow(v.y, 2) + \
		pow(v.z, 2) \
	);
	return (magnitude);
}

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vec3_angle(t_vec3 v1, t_vec3 v2)
{
	float	magnitude1;
	float	magnitude2;
	float	dot;
	float	radians;

	magnitude1 = vec3_magnitude(v1);
	magnitude2 = vec3_magnitude(v2);
	dot = vec3_dot(v1, v2);
	radians = (acos(dot / (magnitude1 * magnitude2)));
	return (radians);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return (v3);
}

t_vec3	unit_vector(t_vec3 v)
{
	return vec3_scale(v, vec3_len(v));
}
