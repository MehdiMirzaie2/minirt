#include "minirt.h"

// int	key_hook(int keycode, t_rt *rt, mat4x4 matProj, mesh meshCube)
int	key_hook(int keycode, t_rt *rt)
{
	// rt->fElapsedTime += 10;
	(void)rt;
	if (keycode == UP)
		main();
		// draw(rt, matProj, meshCube);
	return 0;
}
