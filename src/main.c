/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/12 17:57:13 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
    int *buffer;

    buffer = rt->pointer_to_image;
    buffer[(y * rt->size_line / 4) + x] = color;
}

void MultiplyMatrixVector(t_vec3 *i, t_vec3 *o, t_mat4 *m)
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
	t_mat4	m;

	m = rotate_camera();
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            t_vec3	point1;
            t_vec2	point = (t_vec2){x, y};
            point.x /= (float)SIZE;
            point.y /= (float)SIZE;
            point.x = point.x * 2.0f - 1.0f; // -1 -> 1
            point.y = point.y * 2.0f - 1.0f;
            MultiplyMatrixVector(&(t_vec3){point.x , point.y, -1.0}, &point1, rt->matProj);
            ft_sphere(rt, point, (t_vec2){x, y});
        }
    }
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
}

//void test_parser(t_map *map)
//{
//	while (map)
//	{
//		if (!ft_strncmp(map->type, "A", 1))
//			printf("A: %f\t %d,%d,%d\n", map->light, map->rgb[0], map->rgb[1], map->rgb[2]);
//		if (!ft_strncmp(map->type, "C", 1))
//			printf("C: %f,%f,%f\t %f,%f,%f\t %d\n", map->pos.x, map->pos.y,
//				map->pos.z, map->dir.x, map->dir.y, map->dir.z, map->fov);
//		if (!ft_strncmp(map->type, "L", 1))
//			printf("L: %f,%f,%f\t %f\t %d,%d,%d\n", map->pos.x, map->pos.y,
//				map->pos.z, map->brightness, map->rgb[0], map->rgb[1], map->rgb[2]);
//		if (!ft_strncmp(map->type, "SP", 2))
//			printf("sp: %f,%f,%f\t %f\t %d,%d,%d\n", map->pos.x, map->pos.y,
//				map->pos.z, map->diameter, map->rgb[0], map->rgb[1], map->rgb[2]);
//		if (!ft_strncmp(map->type, "PL", 2))
//			printf("pl: %f,%f,%f\t %f,%f,%f\t %d,%d,%d\n", map->pos.x, map->pos.y,
//				map->pos.z, map->dir.x, map->dir.y, map->dir.z, map->rgb[0], map->rgb[1], map->rgb[2]);
//		if (!ft_strncmp(map->type, "CY", 2))
//		map = map->next;
//	}
//}

int main(int argc, char **argv)
{
    t_rt *rt;

	if (argc != 2)
	{
		printf("Wrong arguments.\n");
		exit(1);
	}
    rt = malloc(sizeof(t_rt));
    init_rt(rt);
    init_mlx(rt);
    rt->matProj = init_matProj();
    parse(&rt->map, argv[1]);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, mouse_hook, rt);
    mlx_loop_hook(rt->mlx, loop, rt);
    mlx_loop(rt->mlx);
    return 0;
}
