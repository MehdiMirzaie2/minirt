/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/27 11:22:00 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include "rt.h"
// #include "map.h"
#include "minirt.h"

void put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
    int *buffer;

    buffer = rt->pointer_to_image;
    buffer[(y * rt->size_line / 4) + x] = color;
}

// void MultiplyMatrixVector(t_vec3d *i, t_vec3d *o, t_mat4x4 *m)
// {
//     o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
//     o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
//     o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
//     float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];
//     if (w != 0.0f)
//     {
//         o->x /= w;
//         o->y /= w;
//         o->z /= w;
//     }
// }

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


t_vec3d clamp(t_vec3d value, t_vec3d min, t_vec3d max)
{
    t_vec3d result = value;
    
    if (value.r < min.r)
        result.r = min.r;
    else if (value.r > max.r)
        result.r = max.r;
    if (value.g < min.g)
        result.g = min.g;
    else if (value.g > max.g)
        result.g = max.g;
    if (value.b < min.b)
        result.b = min.b;
    else if (value.b > max.b)
        result.b = max.b;
    return (result);
}

/*
    a = ray origin -> forward negative z.
    b = ray direction
    r = radius
    t = hitpoint
*/
void render(t_rt *rt)
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

    t_map   *closest_obj = NULL;

    t_vec2d point;

    clearScreen(rt);
	camera()->mat = rotate_camera();
    // printf("c%f\n", camera()->pos.z);
    if (rt->map)
    {
        for (uint32_t y = 0; y < SIZE; y++)
        {
            for (uint32_t x = 0; x < SIZE; x++)
            {
                t_vec3d colour = per_pixal(rt, x, y);
                colour = clamp(colour, (t_vec3d){0.0f, 0.0f, 0.0f}, (t_vec3d){255.0f, 255.0f, 255.0f});
                put_color_to_pixel(rt, x, y, ConvertToRGBA(init_vec3d(colour.r, colour.g, colour.b)));
                // t_map   *ref_map = rt->map;
                // closest_obj = NULL;
                // float   closest_t_val ;
                // float   old_closest = __FLT_MAX__;
                // while (ref_map)
                // {
                //     // point = (t_vec2d){x, y};
                //     t_vec2d notnormed = init_vec2d(x, y);
                //     point = init_vec2d(x, y);
                //     point.x /= (float)SIZE;
                //     point.y /= (float)SIZE;
                //     point.x = point.x * 2.0f - 1.0f;
                //     point.y = point.y * 2.0f - 1.0f;

                //     if (ref_map->type == E_TTSP)
                //         closest_t_val = ft_sphere(ref_map, point, notnormed);
                //     else if (ref_map->type == E_TTCY)
                //         closest_t_val = ft_cylinder(rt, ref_map, point, notnormed);
                //         // closest_t_val = ft_cone(ref_map, point, notnormed);
                //     else if (ref_map->type == E_TTPL)
                //         closest_t_val = plane(ref_map, point, notnormed);
                //     if (closest_t_val < old_closest)
                //     {
                //         old_closest = closest_t_val;
                //         closest_obj = ref_map;
                //         // printf("%d\n", closest_obj->type);
                //     }
                //     ref_map = ref_map->next;
                // }
                // if (closest_obj != NULL)
                // {
                //     if (closest_obj->type == E_TTSP)
                //     {
                //         t_vec3d rayDirections = init_vec3d(point.x, point.y, -1.0f);
                //         t_vec3d rayOrigin = closest_obj->point;
                //         t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, old_closest));
                //         t_vec3d normal = hit_point;
                //         normalize(&normal);
                //         normalize(&rt->light_dir);
                //         float intensity = max(dot(normal, t_vec3d_scale(rt->light_dir, -1)), 0.0);
                //         put_color_to_pixel(rt, x, y, ConvertToRGBA(init_vec3d(intensity, intensity, intensity)));
                //     }
                    
                //     else if (closest_obj->type == E_TTCY)
                //     {
                //        t_vec3d rayDirections = init_vec3d(point.x, point.y, -1.0f);
                //         t_vec3d rayOrigin = closest_obj->point;
                //         t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, old_closest));
                //         t_vec3d normal = hit_point;
                //         normalize(&normal);
                //         normalize(&rt->light_dir);
                //         float intensity = max(dot(normal, t_vec3d_scale(rt->light_dir, -1)), 0.0);
                //         put_color_to_pixel(rt, x, y, ConvertToRGBA(init_vec3d(intensity, intensity, 0xff00ff)));
                //     }

                    
                //     // else if (closest_obj->type == E_TTCN)
                //     // {
                //     //     //  t_vec3d rayDirections = (t_vec3d){point.x, point.y, -1.0f};
                //     //     t_vec3d rayDirections = init_vec3d(point.x, point.y, -1.0f);
                //     //     // t_vec3d rayOrigin = (t_vec3d){-5.0f, 0.0f, 20.0};
                //     //     t_vec3d rayOrigin = init_vec3d(-5.0f, 0.0f, 20.0f);
                //     //     // t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
                //     //     t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, old_closest));
                //     //     t_vec3d normal = hit_point;
                //     //     normalize(&normal);
                //     //     t_vec3d ref_light_dir = rt->light_dir;
                //     //     normalize(&ref_light_dir);
                //     //     rotate_z(&ref_light_dir, rt);
                //     //     float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
                //     //     // put_color_to_pixel(rt, x, y, ConvertToRGBA((t_vec3d){intensity, intensity, 0xFF0000}));
                //     //     put_color_to_pixel(rt, x, y, ConvertToRGBA(init_vec3d(intensity, intensity, 0xFF0000)));
                //     // }
                //     else if (closest_obj->type == E_TTPL)
                //     {
                //         uint32_t color = (0x00 << 24) | ((int)closest_obj->rgb.r << 16) | ((int)closest_obj->rgb.g << 8) | (int)closest_obj->rgb.b;
                //         put_color_to_pixel(rt, x, y, color);
                //     }
                // }
            }
        }
    }
    rt->fTheta += 0.01;
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
    // printf("looping\n");
    // exit(0);
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
				map->point.z, map->normalized.x, map->normalized.y, map->normalized.z, map->rgb.r, map->rgb.g, map->rgb.b);
		if (map->type == E_TTCY)
			printf("cy: point: %f,%f,%f\t normalized: %f,%f,%f\t diameter: %f\t height: %f\t rgb: %f,%f,%f\n", map->point.x, map->point.y,
				map->point.z, map->normalized.x, map->normalized.y, map->normalized.x, map->diameter, map->height, map->rgb.r, map->rgb.g, map->rgb.b);
		map = map->next;
	}
}

int main(int ac, char **av)
{
    t_rt *rt;

	if (ac != 2)
	{
		printf("Wrong arguments.\n");
		exit(1);
	}
    rt = malloc(sizeof(t_rt));
    init_rt(rt);
    init_mlx(rt);
    if (ac != 2)
        return (1);
    parse(&rt->map, av[1]);
    // test_parser(rt->map);
    // get_camera()
	set_camera(rt);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, (void *)mouse_hook, rt);

    mlx_loop_hook(rt->mlx, (void *)render, rt);
    mlx_loop(rt->mlx);
    return 0;
}
