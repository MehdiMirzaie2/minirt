/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:19:52 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/27 15:40:01 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include "map.h"
#include "minirt.h"

void	put_color_to_pixel(t_rt *rt, int x, int y, int color)
{
	int	*buffer;

	buffer = rt->pointer_to_image;
	buffer[(y * rt->size_line / 4) + x] = color;
}

int	draw_rt(t_rt *rt)
{
	rt->x = 0;
	rt->y = 0;
	while (rt->x < SIZE)
	{
		while (rt->y < SIZE)
		{
			put_color_to_pixel(rt, rt->x, rt->y, 0xFF0000);
			rt->y++;
		}
		rt->x++;
		rt->y = 0;
	}
	mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0,
		0);
	return (0);
}

int	main(int ac, char **av)
{
	t_rt *rt;

	if (ac != 2)
		return (-1);
	rt = malloc(sizeof(t_rt));

	parse(&rt->map, av[1]);

	init_rt(rt);
	init_mlx(rt);
	// mlx_key_hook(rt->window, key_hook, rt);
	// mlx_mouse_hook(rt->window, mouse_hook, rt);
	// mlx_hook(rt->window, 17, 0L, exit_rt, rt);
	draw_rt(rt);
	mlx_loop(rt->mlx);

	return (0);
}
