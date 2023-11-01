/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/01 16:11:28 by mehdimirzai      ###   ########.fr       */
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

int draw(t_rt *rt)
{
    // printf("in draw\n");
    clearScreen(rt);
    mat4x4 matRotZ = { 0 }, matRotX = { 0 };
    vec3d vCamera = { 0 };
	
    // Rotation Z
    matRotZ.m[0][0] = cosf(rt->fTheta);
    matRotZ.m[0][1] = sinf(rt->fTheta);
    matRotZ.m[1][0] = -sinf(rt->fTheta);
    matRotZ.m[1][1] = cosf(rt->fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(rt->fTheta * 0.5f);
    matRotX.m[1][2] = sinf(rt->fTheta * 0.5f);
    matRotX.m[2][1] = -sinf(rt->fTheta * 0.5f);
    matRotX.m[2][2] = cosf(rt->fTheta * 0.5f);
    matRotX.m[3][3] = 1;
    rt->fTheta+=0.01f;

    // Draw Triangles (the meshCube.tris initialization is not provided here
    for (int i = 0; i < rt->meshCube.num_triangles; i++)
    {
        triangle tri = rt->meshCube.tris[i];
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

        vec3d normal, line1, line2;

		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;
		
		normal.x = line1.y * line2.z - line1.z * line2.y;
		normal.y = line1.z * line2.x - line1.x * line2.z;
		normal.z = line1.x * line2.y - line1.y * line2.x;

		float l = sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
		normal.x /= l; normal.y /= l; normal.z /= l;

        // Project triangles from 3D --> 2D
		// if (normal.z < 0)
        // (void)vCamera;
        // if ((normal.x * (triTranslated.p[0].x - vCamera.x)) + (normal.y * (triTranslated.p[0].y - vCamera.y)) + (normal.z * (triTranslated.p[0].z - vCamera.z) > 0.0f))
        if (normal.z < 0 && ((normal.x * (triTranslated.p[0].x - vCamera.x)) + (normal.y * (triTranslated.p[0].y - vCamera.y)) + (normal.z * (triTranslated.p[0].z - vCamera.z)) < 0.0f))
		{
        
        // Project triangles from 3D --> 2D
        MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], rt->matProj);
        MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], rt->matProj);
        MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], rt->matProj);

        // Scale into view
        triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
		// printf("add 1:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
        triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
        triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
        triProjected.p[0].x *= 0.5f * (float)SIZE;
        triProjected.p[0].y *= 0.5f * (float)SIZE;
		// printf("center:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
        triProjected.p[1].x *= 0.5f * (float)SIZE;
        triProjected.p[1].y *= 0.5f * (float)SIZE;
        triProjected.p[2].x *= 0.5f * (float)SIZE;
        triProjected.p[2].y *= 0.5f * (float)SIZE;

		draw_triangle(rt, triProjected.p[0].x, triProjected.p[0].y,
			triProjected.p[1].x, triProjected.p[1].y,
			triProjected.p[2].x, triProjected.p[2].y);
        }
        // Rasterize triangle (the DrawTriangle function is not provided here)
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
		0);
    return (0);
}



int main(void)
{
	t_rt *rt;
    // mesh meshCube;
    // mat4x4 *matProj;
    // vec3d vCamera;

	rt = malloc(sizeof(t_rt));
	init_rt(rt);
	init_mlx(rt);
    rt->meshCube.num_triangles = 12;
    rt->matProj = init_matProj();
    // Assign the array to meshCube
    // meshCube.tris = triangles;
    rt->meshCube.tris = init_cube();
    mlx_key_hook(rt->window, key_hook, rt);
    // Set up rotation matrices
    // draw(rt, rt->matProj, &rt->meshCube);
    // draw(rt);
    mlx_loop_hook(rt->mlx, draw, rt);
	mlx_loop(rt->mlx);
    return 0;
}















// int main(void)
// {
// 	t_rt *rt;
//     mesh meshCube;
// 	meshCube.num_triangles = 12;
//     mat4x4 *matProj;
//     // vec3d vCamera;

// 	rt = malloc(sizeof(t_rt));
// 	init_rt(rt);
// 	init_mlx(rt);
//     // mlx_key_hook(rt->window, key_hook, rt);

//     matProj = init_matProj();
//     // Assign the array to meshCube
//     // meshCube.tris = triangles;
//     meshCube.tris = init_cube();

//     // Set up rotation matrices
//     draw(rt, matProj, meshCube);
//     mat4x4 matRotZ = { 0 }, matRotX = { 0 };
	
//     // Rotation Z
//     matRotZ.m[0][0] = cosf(rt->fTheta);
//     matRotZ.m[0][1] = sinf(rt->fTheta);
//     matRotZ.m[1][0] = -sinf(rt->fTheta);
//     matRotZ.m[1][1] = cosf(rt->fTheta);
//     matRotZ.m[2][2] = 1;
//     matRotZ.m[3][3] = 1;

//     // Rotation X
//     matRotX.m[0][0] = 1;
//     matRotX.m[1][1] = cosf(rt->fTheta * 0.5f);
//     matRotX.m[1][2] = sinf(rt->fTheta * 0.5f);
//     matRotX.m[2][1] = -sinf(rt->fTheta * 0.5f);
//     matRotX.m[2][2] = cosf(rt->fTheta * 0.5f);
//     matRotX.m[3][3] = 1;

//     // Draw Triangles (the meshCube.tris initialization is not provided here
//     for (int i = 0; i < meshCube.num_triangles; i++)
//     {
//         triangle tri = meshCube.tris[i];
//         triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;
// 		// triangle triProjected, triTranslated;

//         // Rotate in Z-Axis
//         MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
//         MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
//         MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);

//         // Rotate in X-Axis
//         MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
//         MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
//         MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);

//         // Offset into the screen
//         triTranslated = triRotatedZX;
//         triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
//         triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
//         triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

//         vec3d normal, line1, line2;

// 		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
// 		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
// 		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

// 		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
// 		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
// 		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;
		
// 		normal.x = line1.y * line2.z - line1.z * line2.y;
// 		normal.y = line1.z * line2.x - line1.x * line2.z;
// 		normal.z = line1.x * line2.y - line1.y * line2.x;

// 		float l = sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
// 		normal.x /= l; normal.y /= l; normal.z /= l;

//         // Project triangles from 3D --> 2D
// 		// if (normal.z < 0)
//         // if (normal.x * (triTranslated.p[0].x - vCamera.x) + 
//         //     normal.y * (triTranslated.p[0].y - vCamera.y) +
//         //     normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
// 		{
        
//         // Project triangles from 3D --> 2D
//         MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], matProj);
//         MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], matProj);
//         MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], matProj);

//         // Scale into view
//         triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
// 		printf("add 1:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//         triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
//         triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
//         triProjected.p[0].x *= 0.5f * (float)SIZE;
//         triProjected.p[0].y *= 0.5f * (float)SIZE;
// 		printf("center:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//         triProjected.p[1].x *= 0.5f * (float)SIZE;
//         triProjected.p[1].y *= 0.5f * (float)SIZE;
//         triProjected.p[2].x *= 0.5f * (float)SIZE;
//         triProjected.p[2].y *= 0.5f * (float)SIZE;

// 		draw_triangle(rt, triProjected.p[0].x, triProjected.p[0].y,
// 			triProjected.p[1].x, triProjected.p[1].y,
// 			triProjected.p[2].x, triProjected.p[2].y);
//         }
//         // Rasterize triangle (the DrawTriangle function is not provided here)
// 	}
// 	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
// 		0);
// 	mlx_loop(rt->mlx);
//     return 0;
// }
