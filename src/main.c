/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/08 16:38:05 by mmirzaie         ###   ########.fr       */
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
    // printf("zoom level: %f\n", rt->zoom);
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            vec3d   point1;
            vec2d point = (vec2d){x, y};
            point.x /= (float)SIZE;
            point.y /= (float)SIZE;
            point.x = point.x * 2.0f - 1.0f; // -1 -> 1
            point.y = point.y * 2.0f - 1.0f;
            MultiplyMatrixVector(&(vec3d){point.x , point.y, -1.0}, &point1, rt->matProj);
            ft_sphere(rt, point, (vec2d){x, y});
        }
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
    rt->matProj = init_matProj();
    parse(&rt->map, "test.rt");
    // test_parser(rt->map);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, mouse_hook, rt);

    mlx_loop_hook(rt->mlx, loop, rt);
    // loop(rt);
    mlx_loop(rt->mlx);
    return 0;
}



