/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:40:49 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/27 15:11:16 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt(t_rt *rt)
{
	rt->map = malloc(sizeof(t_map));
	rt->x = 0;
	rt->y = 0;
	rt->color = 0xFCBE11;
	rt->zoom = 250;
	rt->offset_x = SIZE / 2;
	rt->offset_y = SIZE / 2;
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