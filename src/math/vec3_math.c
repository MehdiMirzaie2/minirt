#include "minirt.h"

t_vec3	vec3_add(t_vec3 v, t_vec3 u)
{
	return ((t_vec3){v.x + u.x, v.y + u.y, v.z + u.z});
}

t_vec3	vec3_sub(t_vec3 v, t_vec3 u)
{
	return ((t_vec3){v.x - u.x, v.y - u.y, v.z - u.z});
}

t_vec3	vec3_scale(t_vec3 v, float t)
{
	return ((t_vec3){v.x * t, v.y * t, v.z * t});
}

t_vec3	vec3_divide(t_vec3 v, float t)
{
	return ((t_vec3){v.x / t, v.y / t, v.z / t});
}
