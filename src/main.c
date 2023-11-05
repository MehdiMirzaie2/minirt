/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/03 20:10:40 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include "map.h"
#include "minirt.h"
#include <stdbool.h>

void put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
    int *buffer;

    buffer = rt->pointer_to_image;
    buffer[(y * rt->size_line / 4) + x] = color;
}

void MultiplyMatrixVector(vec3d *i, vec3d *o, mat4x4 *m)
{
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f)
    {
        o->x /= w;
        o->y /= w;
        o->z /= w;
    }
}

void clearScreen(t_rt *rt)
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

void normalize(vec3d *vec)
{
    float length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);

    if (length != 0.0f)
    {
        vec->x /= length;
        vec->y /= length;
        vec->z /= length;
    }
}

vec3d vec3d_scale(vec3d v1, float scalar)
{
    vec3d result;

    result.x = v1.x * scalar;
    result.y = v1.y * scalar;
    result.z = v1.z * scalar;
    return (result);
}

vec3d vec3d_add(vec3d v1, vec3d v2)
{
    vec3d result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return (result);
}
// int draw(t_rt *rt)
// {
//     clearScreen(rt);
//     vec3d vCamera = { 0 };

//     // Draw Triangles (the meshCube.tris initialization is not provided here
//     for (int i = 0; i < rt->meshCube.num_triangles; i++)
//     {
//         triangle tri = rt->meshCube.tris[i];
//         triangle triProjected, triTranslated;

//         // Offset into the screen
//         triTranslated = tri;
//         triTranslated.p[0].z += 3.0f;
//         triTranslated.p[1].z += 3.0f;
//         triTranslated.p[2].z += 3.0f;

//         vec3d normal, line1, line2;

// 		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
// 		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
// 		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

// 		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
// 		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
// 		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

// 		normal.x = (line1.y * line2.z) - (line1.z * line2.y);
// 		normal.y = (line1.z * line2.x) - (line1.x * line2.z);
// 		normal.z = (line1.x * line2.y) - (line1.y * line2.x);

// 		float l = sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
// 		normal.x /= l; normal.y /= l; normal.z /= l;

//         // Project triangles from 3D --> 2D
//         if (normal.x * (triTranslated.p[0].x - vCamera.x) +
//             normal.y * (triTranslated.p[0].y - vCamera.y) +
//             normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
// 		{
//             // Project triangles from 3D --> 2D
//             MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], rt->matProj);
//             MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], rt->matProj);
//             MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], rt->matProj);

//             // Scale into view
//             triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
//             // printf("add 1:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//             triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
//             triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
//             triProjected.p[0].x *= 0.5f * (float)SIZE;
//             triProjected.p[0].y *= 0.5f * (float)SIZE;
//             // printf("center:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//             triProjected.p[1].x *= 0.5f * (float)SIZE;
//             triProjected.p[1].y *= 0.5f * (float)SIZE;
//             triProjected.p[2].x *= 0.5f * (float)SIZE;
//             triProjected.p[2].y *= 0.5f * (float)SIZE;

//             draw_triangle(rt, triProjected.p[0].x, triProjected.p[0].y,
//                 triProjected.p[1].x, triProjected.p[1].y,
//                 triProjected.p[2].x, triProjected.p[2].y);

//             draw_fill_tri(rt, triProjected.p[0].x, triProjected.p[0].y,
//                 triProjected.p[1].x, triProjected.p[1].y,
//                 triProjected.p[2].x, triProjected.p[2].y);
//             }
//             // Rasterize triangle (the DrawTriangle function is not provided here)
// 	}
// 	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
// 		0);
//     return (0);
// }

float dot(vec3d v1, vec3d v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// void ft_draw(t_rt *rt, vec2d coord, vec2d notnorm)
// {
//     vec3d point = (vec3d){notnorm.x, notnorm.y, 0};
//     vec3d point1 = (vec3d){notnorm.x, notnorm.y, 0};

//     MultiplyMatrixVector(&point1, &point, rt->matProj);
//     uint8_t r = (uint8_t)((point.x * 255.0f) / SIZE);
//     uint8_t g = (uint8_t)((point.y * 255.0f) / SIZE);
//     put_color_to_pixel(rt, point.x, point.y, 0xFF0000 | (g << 8) | r);
// }

static uint32_t ConvertToRGBA(const vec3d color)
{
    uint8_t r = (uint8_t)(color.x * 255.0f);
    uint8_t g = (uint8_t)(color.y * 255.0f);
    uint8_t b = (uint8_t)(color.z * 255.0f);

    uint32_t result = (0x00 << 24) | (r << 16) | (g << 8) | b;
    return result;
}

float max(float arg1, float arg2)
{
    if (arg1 < arg2)
        return (arg2);
    return (arg1);
}

void ft_draw(t_rt *rt, vec2d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    vec3d rayOrigin = (vec3d){0.0f, 0.0f, 1.0f};
    float radius = 0.5f;
    if (notnorm.x == 370 && notnorm.y == 350)
        printf("break");
    // normalize(&rayDirections);
    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        vec3d fulldir = vec3d_scale(rayDirections, nt);

        vec3d hit_point = vec3d_add(rayOrigin, vec3d_scale(rayDirections, nt));
        vec3d normal = hit_point;
        normalize(&normal);

        // vec3d light_dir = (vec3d){-1, -1, -1};
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, intensity}));
    }
    else
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x000000000);
}

void loop(t_rt *rt)
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            vec2d point = (vec2d){x, y};
            point.x /= (float)SIZE;
            point.y /= (float)SIZE;
            point.x = point.x * 2.0f - 1.0f;
            point.y = point.y * 2.0f - 1.0f;
            ft_draw(rt, point, (vec2d){x, y});
        }
        // printf("%d\n", y);
    }
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
                            0);
}

int main(void)
{
    t_rt *rt;

    rt = malloc(sizeof(t_rt));
    init_rt(rt);
    init_mlx(rt);
    // rt->meshCube.num_triangles = 12;
    rt->matProj = init_matProj();

    // rt->meshCube.tris = init_cube();
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, mouse_hook, rt);
    // draw(rt);
    loop(rt);
    // mlx_loop_hook(rt->mlx, draw, rt);
    mlx_loop(rt->mlx);
    return 0;
}

// int draw(t_rt *rt)
// {
//     clearScreen(rt);
//     mat4x4 matRotZ = { 0 }, matRotX = { 0 };
//     vec3d vCamera = { 0 };

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
//     rt->fTheta += 0.01f;

//     // Draw Triangles (the meshCube.tris initialization is not provided here
//     for (int i = 0; i < rt->meshCube.num_triangles; i++)
//     {
//         triangle tri = rt->meshCube.tris[i];
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

// 		normal.x = (line1.y * line2.z) - (line1.z * line2.y);
// 		normal.y = (line1.z * line2.x) - (line1.x * line2.z);
// 		normal.z = (line1.x * line2.y) - (line1.y * line2.x);

// 		float l = sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
// 		normal.x /= l; normal.y /= l; normal.z /= l;

//         // Project triangles from 3D --> 2D
//         if (normal.x * (triTranslated.p[0].x - vCamera.x) +
//             normal.y * (triTranslated.p[0].y - vCamera.y) +
//             normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
// 		{
//             // Project triangles from 3D --> 2D
//             MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], rt->matProj);
//             MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], rt->matProj);
//             MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], rt->matProj);

//             // Scale into view
//             triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
//             // printf("add 1:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//             triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
//             triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
//             triProjected.p[0].x *= 0.5f * (float)SIZE;
//             triProjected.p[0].y *= 0.5f * (float)SIZE;
//             // printf("center:\t x = %f,\t y=%f \n", triProjected.p[0].x, triProjected.p[0].y);
//             triProjected.p[1].x *= 0.5f * (float)SIZE;
//             triProjected.p[1].y *= 0.5f * (float)SIZE;
//             triProjected.p[2].x *= 0.5f * (float)SIZE;
//             triProjected.p[2].y *= 0.5f * (float)SIZE;

//             draw_triangle(rt, triProjected.p[0].x, triProjected.p[0].y,
//                 triProjected.p[1].x, triProjected.p[1].y,
//                 triProjected.p[2].x, triProjected.p[2].y);

//             draw_fill_tri(rt, triProjected.p[0].x, triProjected.p[0].y,
//                 triProjected.p[1].x, triProjected.p[1].y,
//                 triProjected.p[2].x, triProjected.p[2].y);
//             }
//             // Rasterize triangle (the DrawTriangle function is not provided here)
// 	}
// 	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
// 		0);
//     return (0);
// }