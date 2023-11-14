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
	t_vec3	normed_vec;

	l = vec3_len(v);
	if (l != 0.0)
		vec3_divide(normed_vec, l);
	else
	{
		normed_vec.x = v.x;
		normed_vec.y = v.y;
		normed_vec.z = v.z;
	}
	return (normed_vec);
}
