/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:40:49 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/02 15:55:49 by mehdimirzai      ###   ########.fr       */
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

triangle	*init_cube(void)
{
	triangle *triangles = malloc(sizeof(triangle) * 12);
	
	// face front
	triangles[0].p[0] = (vec3d){0.0f, 0.0f, 0.0f};
    triangles[0].p[1] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[0].p[2] = (vec3d){1.0f, 1.0f, 0.0f};

	triangles[1].p[0] = (vec3d){0.0f, 0.0f, 0.0f};
    triangles[1].p[1] = (vec3d){1.0f, 1.0f, 0.0f};
    triangles[1].p[2] = (vec3d){1.0f, 0.0f, 0.0f};

	// face right
	triangles[2].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[2].p[1] = (vec3d){1.0f, 1.0f, 0.0f};
    triangles[2].p[2] = (vec3d){1.0f, 1.0f, 1.0f};

	triangles[3].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[3].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[3].p[2] = (vec3d){1.0f, 0.0f, 1.0f};

	// face back
	triangles[4].p[0] = (vec3d){1.0f, 0.0f, 1.0f};
    triangles[4].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[4].p[2] = (vec3d){0.0f, 1.0f, 1.0f};

	triangles[5].p[0] = (vec3d){1.0f, 0.0f, 1.0f};
    triangles[5].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[5].p[2] = (vec3d){0.0f, 0.0f, 1.0f};

	// face left
	triangles[6].p[0] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[6].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[6].p[2] = (vec3d){0.0f, 1.0f, 0.0f};

	triangles[7].p[0] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[7].p[1] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[7].p[2] = (vec3d){0.0f, 0.0f, 0.0f};

	// face Top
	triangles[8].p[0] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[8].p[1] = (vec3d){0.0f, 1.0f, 1.0f};
    triangles[8].p[2] = (vec3d){1.0f, 1.0f, 1.0f};

	triangles[9].p[0] = (vec3d){0.0f, 1.0f, 0.0f};
    triangles[9].p[1] = (vec3d){1.0f, 1.0f, 1.0f};
    triangles[9].p[2] = (vec3d){1.0f, 1.0f, 0.0f};

	// face Bottom
	triangles[10].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[10].p[1] = (vec3d){0.0f, 0.0f, 1.0f};
    triangles[10].p[2] = (vec3d){0.0f, 0.0f, 0.0f};

	triangles[11].p[0] = (vec3d){1.0f, 0.0f, 0.0f};
    triangles[11].p[1] = (vec3d){1.0f, 0.0f, 1.0f};
    triangles[11].p[2] = (vec3d){0.0f, 0.0f, 1.0f};
	return (triangles);
}

void	init_rt(t_rt *rt)
{
	rt->map = malloc(sizeof(t_map));
	rt->fTheta = 0.0f;
	// rt->x = 0;
	// rt->y = 0;
	rt->color = 0xFCBE11;
	// rt->zoom = 250;
	// rt->offset_x = SIZE / 2;
	// rt->offset_y = SIZE / 2;
	rt->matProj = NULL;
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