/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/15 14:26:27 by mmirzaie         ###   ########.fr       */
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

void MultiplyMatrixVector(t_vec3d *i, t_vec3d *o, t_mat4x4 *m)
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


/*
    a = ray origin -> forward negative z.
    b = ray direction
    r = radius
    t = hitpoint
*/

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
            // t_vec3d   point1;
            t_vec2d point = (t_vec2d){x, y};
            point.x /= (float)SIZE;
            point.y /= (float)SIZE;
            point.x = point.x * 2.0f - 1.0f;
            point.y = point.y * 2.0f - 1.0f;
            // MultiplyMatrixVector(&(t_vec3d){point.x , point.y, -1.0}, &point1, rt->matProj);
            // ft_cone(rt, (t_vec3d){coord.x, coord.y, -1.0}, notnorm) == 0)
            // ft_cylinder(rt, (t_vec3d){point.x, point.y, -1.0}, (t_vec2d){x, y});
            plane(rt, point, (t_vec2d){x, y});
            // plane2(rt, point, (t_vec2d){x, y});
            // plane3(rt, point, (t_vec2d){x, y});
            // plane4(rt, point, (t_vec2d){x, y});
            ft_sphere(rt, point, (t_vec2d){x, y});
        }
    }
    rt->fTheta += 0.01;
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
                            0);
}

void test_parser(t_map *map)
{
	while (map)
	{
		if (map->type == 'A')
			printf("A:  light: %f\t rgb: %f,%f,%f\n", map->light, map->rgb.r, map->rgb.g, map->rgb.b);
		if (map->type == 'C')
			printf("C:  point: %f,%f,%f\t normalized: %f,%f,%f\t fov: %d\n", map->point.x, map->point.y,
				map->point.z, map->normalized.x, map->normalized.y, map->normalized.z, map->fov);
		if (map->type == 'L')
			printf("L:  point: %f,%f,%f\t brightness: %f\t rgb: %f,%f,%f\n", map->point.x, map->point.y,
				map->point.z, map->brightness, map->rgb.r, map->rgb.g, map->rgb.b);
		if (map->type == E_TTSP)
			printf("sp: point: %f,%f,%f\t diameter: %f\t rgb: %f,%f,%f\n", map->point.x, map->point.y,
				map->point.z, map->diameter, map->rgb.r, map->rgb.g, map->rgb.b);
		if (map->type == E_TTPL)
			printf("pl: point: %f,%f,%f\t normalized: %f,%f,%f\t rgb: %f,%f,%f\n", map->point.x, map->point.y,
				map->point.z, map->normalized.x, map->normalized.y, map->normalized.x, map->rgb.r, map->rgb.g, map->rgb.b);
		if (map->type == E_TTCY)
			printf("cy: point: %f,%f,%f\t normalized: %f,%f,%f\t diameter: %f\t height: %f\t rgb: %f,%f,%f\n", map->point.x, map->point.y,
				map->point.z, map->normalized.x, map->normalized.y, map->normalized.x, map->diameter, map->height, map->rgb.r, map->rgb.g, map->rgb.b);
		map = map->next;
	}
}

int main(void)
{
    t_rt *rt;

    rt = malloc(sizeof(t_rt));
    init_rt(rt);
    init_mlx(rt);
    // rt->matProj = init_matProj();
    parse(&rt->map, "test.rt");
    test_parser(rt->map);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, (void *)mouse_hook, rt);

    mlx_loop_hook(rt->mlx, (void *)loop, rt);
    // loop(rt);
    mlx_loop(rt->mlx);
    return 0;
}



