#include "minirt.h"

float	vec3_len_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_len_squared(v)));
}

t_vec3	vec3_normalized(t_vec3 v)
{
	float	l;

	l = vec3_len(v);
	vec3_divide(v, l);

	return (v);
}
