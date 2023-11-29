/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/29 13:45:36 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "minirt.h"

void put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
    int *buffer;

    buffer = rt->pointer_to_image;
    buffer[(y * rt->size_line / 4) + x] = color;
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
void render(t_rt *rt)
{
    t_map   *closest_obj = NULL;
    t_vec2d point;

    clearScreen(rt);
	camera()->mat = rotate_camera();

	t_vec3d	dir;
	t_vec3d	hit_point;
	t_vec3d	normal;
	t_vec3d	lvec;
	float	light_ratio = 0.0f;
	t_vec3d color;

    if (rt->map)
    {
        for (int y = 0; y < SIZE; y++)
        {
            for (int x = 0; x < SIZE; x++)
            {
                t_map   *ref_map = rt->map;
                closest_obj = NULL;
                float   closest_t_val ;
                float   old_closest = __FLT_MAX__;

				point = init_vec2d(x, y);
				point.x /= (float)SIZE;
				point.y /= (float)SIZE;
				point.x = point.x * 2.0f - 1.0f;
				point.y = point.y * 2.0f - 1.0f;

				t_vec3d vec = init_vec3d(point.x, point.y, -1.0f);
				t_vec3d ray = dir_from_mat(&camera()->mat, vec);
                while (ref_map)
                {
                    if (ref_map->type == E_TTSP)
                        closest_t_val = ft_sphere(ref_map, ray);
                    else if (ref_map->type == E_TTCY)
                        closest_t_val = ft_cylinder(ref_map, ray);
                    else if (ref_map->type == E_TTPL)
                        closest_t_val = plane(ref_map, ray);
                    if (closest_t_val < old_closest)
                    {
                        old_closest = closest_t_val;
                        closest_obj = ref_map;
                    }
                    ref_map = ref_map->next;
                }
                if (closest_obj != NULL)
                {
                    if (closest_obj->type == E_TTSP)
                    {
						dir = t_vec3d_scale(ray, old_closest);
						hit_point = t_vec3d_add(camera()->pos, dir);
						normal = t_vec3d_sub(hit_point, closest_obj->point);
						lvec = t_vec3d_sub(light()->pos, hit_point);
						light_ratio = diffuse_light(normal, lvec);
						light_ratio = specular_light(normal, lvec, t_vec3d_scale(dir, -1), light_ratio);

						color = color_multiply(closest_obj->rgb, light_ratio);
						put_color_to_pixel(rt, x, y, ConvertToRGBA(color));
                    }
                    else if (closest_obj->type == E_TTCY)
                    {
						dir = t_vec3d_scale(ray, old_closest);
						hit_point = t_vec3d_add(camera()->pos, dir);
						normal = t_vec3d_sub(hit_point, closest_obj->point);
						lvec = t_vec3d_sub(light()->pos, hit_point);
						light_ratio = diffuse_light(normal, lvec);

						color = color_multiply(closest_obj->rgb, light_ratio);
						put_color_to_pixel(rt, x, y, ConvertToRGBA(color));
                    }
                    else if (closest_obj->type == E_TTPL)
                    {
						//dir = t_vec3d_scale(ray, old_closest);
						//hit_point = t_vec3d_add(camera()->pos, dir);
						//normal = t_vec3d_sub(hit_point, closest_obj->point);
						//lvec = t_vec3d_sub(light()->pos, hit_point);
						//light_ratio = diffuse_light(normal, lvec);
						color = color_multiply(closest_obj->rgb, 0.5f);
						put_color_to_pixel(rt, x, y, ConvertToRGBA(color));
                    }
                }
            }
        }
    }
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
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
    parse(&rt->map, av[1]);
    test_parser(rt->map);
    mlx_key_hook(rt->window, key_hook, rt);
    mlx_mouse_hook(rt->window, (void *)mouse_hook, rt);

	render(rt);
    mlx_loop(rt->mlx);
    return 0;
}
