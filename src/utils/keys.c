#include "minirt.h"

// int	ismousedown(int button)
// {
// 	// if (button == )
// 	printf("mouse button = %d\n", button);
// }

int	key_hook(int keycode, t_rt *rt)
{
	// mlx_hook(rt->window, 4, 0, ismousedown, rt);
	if (keycode == UP)
		camera()->pos.z -= 0.1f;
	else if (keycode == DOWN)
		camera()->pos.z += 0.1f;
	else if (keycode == LEFT)
		camera()->pos.x -= 0.1f;
	else if (keycode == RIGHT)
		camera()->pos.x += 0.1f;
	else if (keycode == W)
		camera()->pos.y -= 0.1f;
	else if (keycode == S)
		camera()->pos.y += 0.1f;
	else if (keycode == D)
		camera()->dir.x += 0.1f;
	else if (keycode == A)
		camera()->dir.x -= 0.1f;
	else if (keycode == C)
		camera()->dir.z += 0.1f;
	else if (keycode == V)
		camera()->dir.z -= 0.1f;
	else if (keycode == ESC)
		exit_mlx(rt);
	rt->frameindex = 1;
	render(rt);
	return 0;
}

// void	update_light_dir(t_vec3d	*light_dir, int x, int y)
// {
// 	light_dir->x = (float)x / (float)SIZE;
// 	light_dir->y = (float)y / (float)SIZE;
// 	light_dir->x = (light_dir->x * 2.0f - 1.0f);
// 	light_dir->y = (light_dir->y * 2.0f - 1.0f);
// 	light_dir->z = -1;
// }

// void	mouse_hook(int mousecode, int x, int y, t_rt *rt)
// {
// 	if (mousecode == 1)
// 		update_light_dir(&rt->light_dir, x, y);
// 	else if (mousecode == 5)
// 		rt->zoom += 0.1f;
// 	else if (mousecode == 4)
// 		rt->zoom -= 0.1f;
// 	rt->frameindex = 1;
// 	render(rt);
// }
