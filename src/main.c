/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/15 20:53:14 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	mlx_mouse_get_pos(rt->window, &rt->x, &rt->y);
	if (rt->x != rt->x_ref || rt->y != rt->y_ref)
	{
		update_light_dir(&rt->light_dir, rt->x, rt->y);
		rt->x_ref = rt->x;
		rt->y_ref = rt->y;
	}
	clearScreen(rt);
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
    mlx_loop_hook(rt->mlx, render, rt);
    mlx_loop(rt->mlx);
    return 0;
}
