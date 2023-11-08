#include "minirt.h"

float	vec3_len_squared(vec3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	vec3_len(vec3d v)
{
	return (sqrt(vec3_len_squared(v)));
}

float	vec3_normalize(vec3d v)
{
	float	l;

	l = vec3_len(v);
	vec3_divide(v, l);

	return (l);
}

vec3d	vec3_normalized(void)
{
	vec3d	*v;

	v = malloc(sizeof(vec3d));
	vec3_normalize(*v);
	return (*v);
}
