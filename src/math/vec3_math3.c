#include "minirt.h"

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vec3_angle(t_vec3 v1, t_vec3 v2)
{
	float	len1;
	float	len2;
	float	dot;
	float	radians;

	len1 = vec3_len(v1);
	len2 = vec3_len(v2);
	dot = vec3_dot(v1, v2);
	radians = (acos(dot / (len1 * len2)));
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
