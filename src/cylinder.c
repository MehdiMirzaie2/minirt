#include "minirt.h"
#include "../include/vec3.h"

int	init_cylinder(t_map map)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	*cy = (t_cylinder)
	{
		.radius = map.diameter / 2.0,
		.height = map.height,
		.center = (t_vec3){(double)map.point[0], (double)map.point[1], (double)map.point[2]},
		.normal = (t_vec3){(double)map.normalized[0], (double)map.normalized[1], (double)map.normalized[2]},
		.color = (t_color){(double)map.rgb[0], (double)map.rgb[1], (double)map.rgb[2]}
	};
	if (vec3_len(cy->normal) < 1.0 - 0.0001 \
		|| cy->radius < 0.0001 || cy->height < 0.0001)
		return (0);
	cy->normal = unit_vector(cy->normal);
	cy->cap1 = vec3_add(cy->center, vec3_multifly(cy->normal, -cy->height / 2.0));
	cy->cap2 = vec3_add(cy->center, vec3_multifly(cy->normal, -cy->height / 2.0));
	return (1);
}

//int	draw_cylinder()

