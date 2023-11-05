#include "minirt.h"

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == UP)
	{
		clearScreen(rt);
		rt->fTheta += 0.001f;
		// draw(rt);
	}
	return 0;
}

void	mouse_hook(int mousecode, int x, int y, t_rt *rt)
{
	printf("x= %d\t y= %d\n", x, y);
	// float newx = (float)x / (float)SIZE;
	// float newy = (float)y / (float)SIZE;

	// newx = newx * 2.0f - 1.0f;
	// newy = newy * 2.0f - 1.0f;
	vec2d point = (vec2d){x, y};
	point.x /= (float)SIZE;
	point.y /= (float)SIZE;
	point.x = point.x * 2.0f - 1.0f;
	point.y = point.y * 2.0f - 1.0f;
	// point.x = point.x * 2.0f - 1.0f;
    // point.y = point.y * 2.0f - 1.0f;
	printf("new x= %f\t new y= %f\n", point.x, point.y);
	// rt->light_dir = (vec3d){(x / (float)SIZE), (y / (float)SIZE), -1};
	rt->light_dir = (vec3d){-point.x, -point.y, -1};
	printf("%d\n", mousecode);
	clearScreen(rt);
	loop(rt);
	// draw_fractal(fractal, fractal->cx, fractal->cy);
}
