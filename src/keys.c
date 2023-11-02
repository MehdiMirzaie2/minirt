#include "minirt.h"

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == UP)
	{
		clearScreen(rt);
		rt->fTheta += 0.001f;
		draw(rt);
	}
	return 0;
}
