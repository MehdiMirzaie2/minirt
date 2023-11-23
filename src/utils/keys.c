#include "minirt.h"

int	key_hook(int keycode, t_rt *rt)
{
	printf("keycode - %i\n", keycode);
	if (keycode == UP)
	{
		// clearScreen(rt);
		//rt->fTheta += 0.001f;
		// draw(rt);
		camera()->pos.z -= 0.5f;
	}
	else if (keycode == DOWN)
		camera()->pos.z += 0.5f;
	else if (keycode == LEFT)
		camera()->pos.x += 0.5f;
	else if (keycode == RIGHT)
		camera()->pos.x -= 0.5f;
	else if (keycode == W)
		camera()->dir.y += 0.1f;
	else if (keycode == S)
		camera()->dir.y -= 0.1f;
	else if (keycode == D)
		camera()->dir.x -= 0.1f;
	else if (keycode == A)
		camera()->dir.x += 0.1f;
	else if (keycode == C)
		camera()->dir.z += 0.1f;
	else if (keycode == V)
		camera()->dir.z -= 0.1f;
	else if (keycode == ESC)
		exit_mlx(rt);
	render(rt);
	return 0;
}

void	update_light_dir(t_vec3d	*light_dir, int x, int y)
{
	light_dir->x = (float)x / (float)SIZE;
	light_dir->y = (float)y / (float)SIZE;
	light_dir->x = (light_dir->x * 2.0f - 1.0f);
	light_dir->y = (light_dir->y * 2.0f - 1.0f);
	light_dir->z = -1;
}

void	mouse_hook(int mousecode, int x, int y, t_rt *rt)
{
	// printf("%d\n", mousecode);
	if (mousecode == 1)
	{
		update_light_dir(&rt->light_dir, x, y);
	}
	else if (mousecode == 5)
	{
		// printf("zomming\n");
		rt->zoom += 0.1f;
	}
	else if (mousecode == 4)
	{
		rt->zoom -= 0.1f;
	}
	render(rt);
}
