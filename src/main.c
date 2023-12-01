/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:03 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
	int *buffer;

	buffer = rt->pointer_to_image;
	buffer[(y * rt->size_line / 4) + x] = color;
}

void clear_screen(t_rt *rt)
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
	t_vec3d result;

	result = value;
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
	t_map *closest_obj;
	int y;
	int x;
	t_vec3d colour;
	t_vec3d accum_colour;

	closest_obj = NULL;
	clear_screen(rt);
	camera()->mat = rotate_camera();
	// if (rt->frameindex == 1)
	//     ft_memset()
	// printf("c%f\n", camera()->pos.z);
	y = -1;
	if (rt->map)
	{
		while (++y < SIZE)
		{
			x = -1;
			while (++x < SIZE)
			{
				colour = per_pixal(rt, x, y);

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
				put_color_to_pixel(rt, x, y, convert_to_rgba(colour));
			}
		}
	}
	rt->fTheta += 0.01;
	rt->frameindex++;
	// printf("%d\n", rt->frameindex);
	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
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
	mlx_hook(rt->window, 2, 0, key_hook, rt);
	mlx_mouse_hook(rt->window, (void *)mouse_hook, rt);
	mlx_loop_hook(rt->mlx, (void *)render, rt);
	mlx_hook(rt->window, 17, 0L, exit_mlx, rt);
	mlx_loop(rt->mlx);
	return (0);
}
