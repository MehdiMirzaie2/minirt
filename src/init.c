/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:40:49 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/08 15:29:50 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

mat4x4	*init_matProj(void)
{
	mat4x4 *matProj = malloc(sizeof(mat4x4));
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)SIZE / (float)SIZE;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.f * 3.14159f);

	if (matProj->m != NULL)
    	ft_memset(matProj, 0.0f, sizeof(mat4x4));
	matProj->m[0][0] = fAspectRatio * fFovRad;
	matProj->m[1][1] = fFovRad;
	matProj->m[2][2] = fFar / (fFar - fNear);
	matProj->m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj->m[2][3] = 1.0f;
	matProj->m[3][3] = 0.0f;
	return (matProj);
}

void	init_rt(t_rt *rt)
{
	rt->map = malloc(sizeof(t_map));
	rt->fTheta = 2.0f;
	rt->x = -1;
	rt->y = -1;
	rt->x_ref = -1;
	rt->y_ref = -1;
	rt->color = 0xFCBE11;
	rt->zoom = 1.0f;

	rt->camera = (vec2d){0, 0};
	rt->matProj = init_matProj();
	rt->meshCube.num_triangles = 0;
	rt->meshCube.tris = NULL;
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
	free(rt->mlx);
	free(rt);
	exit(0);
}
