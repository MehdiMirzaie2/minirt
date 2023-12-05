/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:40:49 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 15:28:23 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt(t_rt *rt)
{
	rt->hitable = malloc(sizeof(t_hitable));
	rt->theta = 2.0f;
	rt->mincolour = init_vec3d(0, 0, 0);
	rt->maxcolour = init_vec3d(255, 255, 255);
	rt->i = -1;
	rt->mul = 1.0f;
}

void	init_mlx(t_rt *rt)
{
	rt->mlx = mlx_init();
	rt->window = mlx_new_window(rt->mlx, SIZE, SIZE, "minirt");
	rt->image = mlx_new_image(rt->mlx, SIZE, SIZE);
	rt->pointer_to_image = mlx_get_data_addr(rt->image,
			&rt->bits_per_pixel,
			&rt->size_line,
			&rt->endian);
}

int	exit_mlx(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->image);
	mlx_destroy_window(rt->mlx, rt->window);
	free(rt->hitable);
	free(rt->mlx);
	free(rt);
	exit(0);
}
