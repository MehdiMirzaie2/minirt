#include "minirt.h"

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == UP)
	{
		// clearScreen(rt);
		rt->fTheta += 0.001f;
		// draw(rt);
	}
	else if (keycode == LEFT)
	{
		rt->camera.x += 0.5;
		rt->camera.y += 0.5;
	}
	else if (keycode == ESC)
		exit_mlx(rt);
	loop(rt);
	return 0;
}

void	update_light_dir(vec3d	*light_dir, int x, int y)
{
	light_dir->x = (float)x / (float)SIZE;
	light_dir->y = (float)y / (float)SIZE;
	light_dir->x = -(light_dir->x * 2.0f - 1.0f);
	light_dir->y = -(light_dir->y * 2.0f - 1.0f);
	light_dir->z = -1;
}

void	mouse_hook(int mousecode, int x, int y, t_rt *rt)
{
	printf("%d\n", mousecode);
	if (mousecode == 1)
	{
		update_light_dir(&rt->light_dir, x, y);

	}
	else if (mousecode == 5)
	{
		rt->zoom += 0.1f;
	}
	else if (mousecode == 4)
	{
		rt->zoom -= 0.1f;
	}
	loop(rt);
}
