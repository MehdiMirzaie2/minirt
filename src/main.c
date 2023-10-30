/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/30 16:56:43 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include "map.h"
#include "minirt.h"


struct vec3d
{
	float x, y, z;
};

struct triangle
{
	vec3d p[3];
};

struct mesh
{
	triangle tris[100];
};

struct mat4x4
{
	float m[4][4] = { 0 };
}

void draw_line(t_fractal *fractal, t_vec p1, t_vec p2)
{
    double dx = abs(p2.x - p1.x);
    int sx = p1.x < p2.x ? 1 : -1;
    double dy = -abs(p2.y - p1.y);
    int sy = p1.y < p2.y ? 1 : -1;
    double error = dx + dy;

    while (1)
    {
        put_color_to_pixel(fractal, p1.x, p1.y, 0xFF0000);
        if (p1.x == p2.x && p1.y == p2.y)
            break ;
        double e2 = 2 * error;
        if (e2 >= dy)
        {
            if (p1.x == p2.x)
                break;
            error = error + dy;
            p1.x = p1.x + sx;
        }
        if (e2 <= dx)
        {
            if (p1.y == p2.y)
                break ;
            error = error + dx;
            p1.y = p1.y + sy;
        }
    }
}

void	draw_triangle(t_fractal *fractal, int x1, int y1, int x2, int y2, int x3, int y3)
{
	t_vec p1 = {x1, y1};
	t_vec p2 = {x2, y2};
	t_vec p2 = {x3, y3};

	draw_line(fractal, p1, p2);
	draw_line(fractal, p2, p3);
	draw_line(fractal, p3, p1);
}

void	put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
	int	*buffer;

	buffer = rt->pointer_to_image;
	buffer[(y * rt->size_line / 4) + x] = color;
}

// int	draw_rt(t_rt *rt)
// {
// 	rt->x = 0;
// 	rt->y = 0;
// 	while (rt->x < SIZE)
// 	{
// 		while (rt->y < SIZE)
// 		{
// 			put_color_to_pixel(rt, rt->x, rt->y, 0xFF0000);
// 			rt->y++;
// 		}
// 		rt->x++;
// 		rt->y = 0;
// 	}
// 	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
// 		0);
// 	return (0);
// }
void	clearScreen(t_rt *rt)
{
	rt->x = 0;
	rt->y = 0;
	while (rt->x < SIZE)
	{
		while (rt->y < SIZE)
		{
			put_color_to_pixel(rt, rt->x, rt->y, 0x000000);
			rt->y++;
		}
		rt->x++;
		rt->y = 0;
	}
}

void

bool onUserUpdate(float fElapsedTime, t_rt *rt);
{
	rt->x = 0;
	rt->y = 0;
	clearScreen(rt);
	while (rt->x < SIZE)
	{
		while (rt->y < SIZE)
		{
			put_color_to_pixel(rt, rt->x, rt->y, 0xFF0000);
			rt->y++;
		}
		rt->x++;
		rt->y = 0;
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
		0);
	return (0);
}

void multiplyMatrixVector(vec3d *i, vec3d *o, mat4x4 *m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.x = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.x = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

int	main(int ac, char **av)
{
	t_rt *rt;
	mesh mesh_cube;
	mat4x4 matProj;

	if (ac != 2)
		return (-1);
	rt = malloc(sizeof(t_rt));

	parse(&rt->map, av[1]);

	mesh_cube.tris = {
		{ 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 1.0f },

		{ 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f },

		{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f },

		// Top
		{ 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 0.0f },

		// Bottom
		{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f },
	};

	// projection Matrix;
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = SIZE / SIZE;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

	init_rt(rt);
	init_mlx(rt);
	// mlx_key_hook(rt->window, key_hook, rt);
	// mlx_mouse_hook(rt->window, mouse_hook, rt);
	// mlx_hook(rt->window, 17, 0L, exit_rt, rt);

	for (int i = 0; i < 50; i++)
	{
		triangle triProjected;
		multiplyMatrixVector()
	}

	draw_rt(rt);
	mlx_loop(rt->mlx);

	return (0);
}
