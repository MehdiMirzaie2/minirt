/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/08 14:30:33 by mmirzaie         ###   ########.fr       */
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

float dot(vec3d v1, vec3d v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

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

/*
    a = ray origin -> forward negative z.
    b = ray direction
    r = radius
    t = hitpoint
*/

int ft_draw(t_rt *rt, vec2d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    vec3d rayOrigin = (vec3d){0.0f, 0.0f, rt->zoom};
    // vec3d rayOrigin = (vec3d){0.0, rt->camera.y, rt->zoom};
    float radius = 0.5f;

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
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, intensity}));
    }
    else
        return (0);
}

void ft_draw2(t_rt *rt, vec2d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    // vec3d rayOrigin = (vec3d){0.0f, 0.0f, rt->zoom};
    vec3d rayOrigin = (vec3d){0.5f, 0.5f, rt->zoom};
    float radius = 0.5f;

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
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, intensity}));
    }
    // else if (ft_draw(rt, coord, notnorm) == 0)
    else
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x000000000);
}

void ft_cone(t_rt *rt, vec2d coord, vec2d notnorm)
{
    vec3d rayDirections = (vec3d){coord.x, coord.y, -1.0f};
    vec3d rayOrigin = (vec3d){0.0f, 0.0f, rt->zoom};
    float radius = 0.5f;

    // (bx^2 - by^2 + bz^2)t^2 + (2(ax)(bx) - 2(ay)(by) + 2(az)(bz))t + (ax^2 - ay^2 + az^2)

    float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
    float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);

        vec3d fulldir = vec3d_scale(rayDirections, nt);

        vec3d hit_point = vec3d_add(rayOrigin, vec3d_scale(rayDirections, nt));
        vec3d normal = hit_point;
        normalize(&normal);
        normalize(&rt->light_dir);
        float intensity = max(dot(normal, vec3d_scale(rt->light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((vec3d){intensity, intensity, 0xFF0000}));
    }
    else
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x000000000);
}

void loop(t_rt *rt)
{
    mlx_mouse_get_pos(rt->window, &rt->x, &rt->y);
    {
        if (rt->x != rt->x_ref || rt->y != rt->y_ref)
        {
            update_light_dir(&rt->light_dir, rt->x, rt->y);
            rt->x_ref = rt->x;
            rt->y_ref = rt->y;
        }
    }
    clearScreen(rt);
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            vec2d point = (vec2d){x, y};
            point.x /= (float)SIZE;
            point.y /= (float)SIZE;
            point.x = point.x * 2.0f - 1.0f; // -1 -> 1
            point.y = point.y * 2.0f - 1.0f;
            ft_cone(rt, point, (vec2d){x, y});
            // ft_cone2(rt, point, (vec2d){x, y});
            // ft_draw(rt, point, (vec2d){x, y});
        }
    }
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
                            0);
}


void test_parser(t_map *map)
{
	while (map)
	{
		if (map->type == 'A')
			printf("A: %f\t %d,%d,%d\n", map->light, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == 'C')
			printf("C: %f,%f,%f\t %f,%f,%f\t %d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->fov);
		if (map->type == 'L')
			printf("L: %f,%f,%f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->brightness, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTSP)
			printf("sp: %f,%f,%f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->diameter, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTPL)
			printf("pl: %f,%f,%f\t %f,%f,%f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTCY)
			printf("cy: %f,%f,%f\t %f,%f,%f\t %f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->diameter, map->height, map->rgb[0], map->rgb[1], map->rgb[2]);
		map = map->next;
	}
}

int main(void)
{
    t_rt *rt;

    rt = malloc(sizeof(t_rt));
    init_rt(rt);
    init_mlx(rt);
    rt->matProj = init_matProj();
    parse(&rt->map, "test.rt");
    test_parser(rt->map);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, mouse_hook, rt);

    mlx_loop_hook(rt->mlx, loop, rt);
    mlx_loop(rt->mlx);
    return 0;
}



