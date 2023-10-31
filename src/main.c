/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/31 13:30:31 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include "map.h"
#include "minirt.h"
#include <stdbool.h>

typedef struct vec2d
{
	float x, y;
} vec2d;

// typedef struct vec3d
// {
// 	float x, y, z;
// } vec3d;

// typedef struct triangle
// {
// 	vec3d p[3];
// } triangle;

// typedef struct mesh
// {
// 	triangle	tris;
// 	struct mesh	*next;
// } mesh;

// typedef struct mat4x4
// {
// 	float m[4][4];
// } mat4x4;

void	put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
	int	*buffer;

	buffer = rt->pointer_to_image;
	buffer[(y * rt->size_line / 4) + x] = color;
}

void draw_line(t_rt *rt, vec2d p1, vec2d p2)
{
    double dx = fabs(p2.x - p1.x);
    int sx = p1.x < p2.x ? 1 : -1;
    double dy = -fabs(p2.y - p1.y);
    int sy = p1.y < p2.y ? 1 : -1;
    double error = dx + dy;

    while (1)
    {
        put_color_to_pixel(rt, p1.x, p1.y, 0xFFFFFF);
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

void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
{
	vec2d p1 = {x1, y1};
	vec2d p2 = {x2, y2};
	vec2d p3 = {x3, y3};

	printf("x = %d\t y = %d\n", x1, y1);
	printf("x = %d\t y = %d\n", x2, y2);
	printf("x = %d\t y = %d\n\n", x3, y3);
	draw_line(rt, p1, p2);
	draw_line(rt, p2, p3);
	draw_line(rt, p3, p1);
}

#include <stdio.h>
#include <math.h>

typedef struct
{
    float x, y, z;
} vec3d;

typedef struct
{
    vec3d p[3];
} triangle;

typedef struct
{
    triangle* tris;
	int num_triangles;
} mesh;

typedef struct
{
    float m[4][4];
} mat4x4;

void MultiplyMatrixVector(vec3d* i, vec3d* o, mat4x4* m)
{
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f)
    {
        o->x /= w; o->y /= w; o->z /= w;
    }
}

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


int main(void)
{
	t_rt *rt;
    mesh meshCube;
	meshCube.num_triangles = 12;
    mat4x4 matProj;

	rt = malloc(sizeof(t_rt));
	init_rt(rt);
	init_mlx(rt);
	clearScreen(rt);
	triangle triangles[12];

	triangles[0].p[0] = (vec3d){0.0f, 0.0f, 0.0f};
    triangles[0].p[1] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[0].p[2] = (vec3d){1.0f, 1.0f, 0.0f};

	triangles[1].p[0] = (vec3d){0.0f, 0.0f, 0.0f};
    triangles[1].p[1] = (vec3d){1.0f, 1.0f, 0.0f};
    triangles[1].p[2] = (vec3d){1.0f, 0.0f, 0.0f};

	triangles[2].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[2].p[1] = (vec3d){1.0f, 1.0f, 0.0f};
    triangles[2].p[2] = (vec3d){1.0f, 1.0f, 1.0f};

	triangles[3].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[3].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[3].p[2] = (vec3d){1.0f, 0.0f, 1.0f};

	triangles[4].p[0] = (vec3d){1.0f, 0.0f, 1.0f};
    triangles[4].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[4].p[2] = (vec3d){0.0f, 1.0f, 1.0f};

	triangles[5].p[0] = (vec3d){1.0f, 0.0f, 1.0f};
    triangles[5].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[5].p[2] = (vec3d){0.0f, 0.0f, 1.0f};

	triangles[6].p[0] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[6].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[6].p[2] = (vec3d){0.0f, 1.0f, 0.0f};

	triangles[7].p[0] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[7].p[1] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[7].p[2] = (vec3d){0.0f, 0.0f, 0.0f};

	triangles[8].p[0] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[8].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[8].p[2] = (vec3d){1.0f, 1.0f, 1.0f};

	triangles[9].p[0] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[9].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[9].p[2] = (vec3d){1.0f, 1.0f, 0.0f};

	triangles[10].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[10].p[1] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[10].p[2] = (vec3d){1.0f, 0.0f, 1.0f};

	triangles[11].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[11].p[1] = (vec3d){0.0f, 0.0f, 0.0f};
    triangles[11].p[2] = (vec3d){0.0f, 0.0f, 1.0f};
	
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)SIZE / (float)SIZE;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

    // Assign the array to meshCube
    meshCube.tris = triangles;

    float fTheta = 0.0f;

    // Set up rotation matrices
    mat4x4 matRotZ, matRotX;
    fTheta += 1.0f;
	
    // Rotation Z
    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(fTheta * 0.5f);
    matRotX.m[1][2] = sinf(fTheta * 0.5f);
    matRotX.m[2][1] = -sinf(fTheta * 0.5f);
    matRotX.m[2][2] = cosf(fTheta * 0.5f);
    matRotX.m[3][3] = 1;

    // Draw Triangles (the meshCube.tris initialization is not provided here
    for (int i = 0; i < meshCube.num_triangles; i++)
    {
        triangle tri = meshCube.tris[i];
        triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;
		// triangle triProjected, triTranslated;

        // Rotate in Z-Axis
        MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
        MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
        MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);

        // Rotate in X-Axis
        MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
        MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
        MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);

        // Offset into the screen
        triTranslated = triRotatedZX;
        triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
        triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
        triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

        // Project triangles from 3D --> 2D
        MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], &matProj);
        MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], &matProj);
        MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], &matProj);

        // Scale into view
        triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
		printf("add 1:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
        triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
        triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
        triProjected.p[0].x *= 0.5f * (float)SIZE;
        triProjected.p[0].y *= 0.5f * (float)SIZE;
		printf("center:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
        triProjected.p[1].x *= 0.5f * (float)SIZE;
        triProjected.p[1].y *= 0.5f * (float)SIZE;
        triProjected.p[2].x *= 0.5f * (float)SIZE;
        triProjected.p[2].y *= 0.5f * (float)SIZE;

		draw_triangle(rt, triProjected.p[0].x, triProjected.p[0].y,
			triProjected.p[1].x, triProjected.p[1].y,
			triProjected.p[2].x, triProjected.p[2].y);
        // Rasterize triangle (the DrawTriangle function is not provided here)
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
		0);
	mlx_loop(rt->mlx);
    return 0;
}


























// void	clearScreen(t_rt *rt)
// {
// 	rt->x = 0;
// 	rt->y = 0;
// 	while (rt->x < SIZE)
// 	{
// 		while (rt->y < SIZE)
// 		{
// 			put_color_to_pixel(rt, rt->x, rt->y, 0x000000);
// 			rt->y++;
// 		}
// 		rt->x++;
// 		rt->y = 0;
// 	}
// }

// bool onUserUpdate(float fElapsedTime, t_rt *rt)
// {
// 	(void)fElapsedTime;
// 	rt->x = 0;
// 	rt->y = 0;
// 	clearScreen(rt);
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
// 	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
// 	return (0);
// }

// void multiplyMatrixVector(vec3d *i, vec3d *o, mat4x4 *m)
// {
// 	o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
// 	o->x = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
// 	o->x = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
// 	float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

// 	if (w != 0.0f)
// 	{
// 		o->x /= w; o->y /= w; o->z /= w;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	t_rt *rt;
// 	mesh mesh_cube;
// 	// mat4x4 matProj;

// 	if (ac != 2)
// 		return (-1);
// 	rt = malloc(sizeof(t_rt));

// 	parse(&rt->map, av[1]);

// 	mesh_cube.tris[0] = {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}};
// 	// mesh mesh_cube = 
// 	// {
// 	// 	{
// 	// 		{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
// 	// 		{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

// 	// 		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
// 	// 		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
// 	// 	}
// 	// };
// 		// { 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 1.0f },
// 		// { 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f },

// 		// { 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f },
// 		// { 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f },

// 		// // Top
// 		// { 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f },
// 		// { 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 0.0f },

// 		// // Bottom
// 		// { 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f },
// 		// { 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f },

// 	// // projection Matrix;
// 	// float fNear = 0.1f;
// 	// float fFar = 1000.0f;
// 	// float fFov = 90.0f;
// 	// float fAspectRatio = SIZE / SIZE;
// 	// float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

// 	// matProj.m[0][0] = fAspectRatio * fFovRad;
// 	// matProj.m[1][1] = fFovRad;
// 	// matProj.m[2][2] = fFar / (fFar - fNear);
// 	// matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
// 	// matProj.m[2][3] = 1.0f;
// 	// matProj.m[3][3] = 0.0f;

// 	// init_rt(rt);
// 	// init_mlx(rt);
	
// 	// while (mesh.tris)
// 	// {
// 	// 	triangle tri_projected;
		
// 	// 	// Project triangles from 3d --> 2d
// 	// 	multiplyMatrixVector(tri.p[0], triprojected.p[0], matProj);
// 	// 	multiplyMatrixVector(tri.p[1], triprojected.p[1], matProj);
// 	// 	multiplyMatrixVector(tri.p[2], triprojected.p[2], matProj);
// 	// }


// 	// draw_rt(rt);
// 	mlx_loop(rt->mlx);

// 	return (0);
// }
