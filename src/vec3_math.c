#include "minirt.h"

vec3d	vec3_add(vec3d v, vec3d u)
{
	return ((vec3d){v.x + u.x, v.y + u.y, v.z + u.z});
}

vec3d	vec3_sub(vec3d v, vec3d u)
{
	return ((vec3d){v.x - u.x, v.y - u.y, v.z - u.z});
}

vec3d	vec3_multiply(vec3d v, float t)
{
	return ((vec3d){v.x * t, v.y * t, v.z * t});
}

vec3d	vec3_divide(vec3d v, float t)
{
	return ((vec3d){v.x / t, v.y / t, v.z / t});
}
