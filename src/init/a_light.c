#include "minirt.h"

t_a_light	*a_light(void)
{
	static t_a_light	a_light;

	return (&a_light);
}

void	set_a_light(t_nothitable map)
{
	a_light()->intensity = map.light;
	a_light()->color.r = map.rgb.r;
	a_light()->color.g = map.rgb.g;
	a_light()->color.b = map.rgb.b;
}


