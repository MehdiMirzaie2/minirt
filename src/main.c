/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/30 12:39:31 by mmirzaie         ###   ########.fr       */
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
    // if (rt->frameindex == 1)
    //     ft_memset()
    // printf("c%f\n", camera()->pos.z);
    if (rt->map)
    {
        for (uint32_t y = 0; y < SIZE; y++)
        {
            for (uint32_t x = 0; x < SIZE; x++)
            {
                t_vec3d colour = per_pixal(rt, x, y);
                // printf("%f\t %f\t %f\n", colour.r, colour.g, colour.b);

                if (rt->frameindex == 1)
                {
                    rt->accum[x + y * SIZE].x = 0;
                    rt->accum[x + y * SIZE].y = 0;
                    rt->accum[x + y * SIZE].z = 0;
                }
                rt->accum[x + y * SIZE] = t_vec3d_add(rt->accum[x + y * SIZE], colour);

                t_vec3d accum_colour = rt->accum[x + y * SIZE];
                accum_colour = t_vec3d_div(accum_colour, rt->frameindex);
                colour = clamp(accum_colour, (t_vec3d){0.0f, 0.0f, 0.0f}, (t_vec3d){255.0f, 255.0f, 255.0f});
                put_color_to_pixel(rt, x, y, ConvertToRGBA(colour));
            }
        }
    }
    rt->fTheta += 0.01;
    rt->frameindex++;
    printf("%d\n", rt->frameindex);
    mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
    // printf("looping\n");
    // exit(0);
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
    rt->frameindex = 1;
    // test_parser(rt->map);
    // mlx_key_hook(rt->window, key_hook, rt);
    mlx_hook(rt->window, 2, 0, key_hook, rt);
    mlx_mouse_hook(rt->window, (void *)mouse_hook, rt);

	// render(rt);
    // mlx_loop(rt->mlx);
    mlx_loop_hook(rt->mlx, (void *)render, rt);
    mlx_loop(rt->mlx);
    return 0;
}
