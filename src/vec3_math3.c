#include "minirt.h"

float	vec3_dot(vec3d v1, vec3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

vec3d	vec3_cross(vec3d v1, vec3d v2)
{
	vec3d	v3;

	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return (v3);
}

vec3d	unit_vector(vec3d v)
{
	return vec3_multiply(v, vec3_len(v));
}
