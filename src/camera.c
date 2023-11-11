#include "minirt.h"

t_camera	*camera(void)
{
	static t_camera	*camera;

	return (&camera);
}

void	set_camera(t_map	map)
{
	camera()->pos.x = map.pos.x;
	camera()->pos.y = map.pos.y;
	camera()->pos.z = map.pos.z;
	camera()->dir.x = map.dir.x;
	camera()->dir.y = map.dir.y;
	camera()->dir.z = map.dir.z;
	set_fov(map.fov);
}
