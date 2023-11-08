#include "../include/vec3.h"

double	vec3_len_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_len_squared(v)));
}

double	vec3_normalize(t_vec3 v)
{
	double	l;

	l = vec3_len(v);
	vec3_divide(v, l);

	return (l);
}

t_vec3	vec3_normalized(void)
{
	t_vec3	*v;

	v = malloc(sizeof(t_vec3));
	vec3_normalize(*v);
	return (*v);
}
