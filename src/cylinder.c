#include "minirt.h"

int	init_cylinder(t_map map)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	*cy = (t_cylinder)
	{
		.radius = map.diameter / 2.0,
		.height = map.height,
		.center = (vec3d){map.point[0], map.point[1], map.point[2]},
		.normal = (vec3d){map.normalized[0], map.normalized[1], map.normalized[2]},
		.color = (t_color){map.rgb[0], map.rgb[1], map.rgb[2]}
	};
	if (vec3_len(cy->normal) < 1.0 - 0.0001 \
		|| cy->radius < 0.0001 || cy->height < 0.0001)
		return (0);
	cy->normal = unit_vector(cy->normal);
	cy->cap1 = vec3_add(cy->center, vec3_multiply(cy->normal, -cy->height / 2.0));
	cy->cap2 = vec3_add(cy->center, vec3_multiply(cy->normal, -cy->height / 2.0));
	return (1);
}

//int	draw_cylinder()

