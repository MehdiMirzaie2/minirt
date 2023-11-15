#include "minirt.h"

t_camera	*camera(void)
{
	static t_camera	*camera;

	return (&camera);
}

void	set_camera(t_map map)
{
	camera()->pos.x = 0.0f;
	camera()->pos.y = 0.0f;
	camera()->pos.z = 1.0f;
	camera()->dir.x = map.dir.x;
	camera()->dir.y = map.dir.y;
	camera()->dir.z = map.dir.z;
}
