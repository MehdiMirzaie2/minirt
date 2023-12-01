/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:57:04 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/01 13:47:10 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void rotate_x(t_vec3d *coord, t_rt *rt)
{
	float t_y;

	t_y = coord->y;
	coord->x = t_y * cos(rt->fTheta) + coord->z * sin(rt->fTheta);
	coord->z = t_y * -sin(rt->fTheta) + coord->z * cos(rt->fTheta);
}

void rotate_y(t_vec3d *coord, t_rt *rt)
{
	float t_x;

	t_x = coord->x;
	coord->x = t_x * cos(rt->fTheta) + coord->z * -sin(rt->fTheta);
	coord->z = t_x * sin(rt->fTheta) + coord->z * cos(rt->fTheta);
}

void rotate_z(t_vec3d *coord, t_rt *rt)
{
	float t_x;

	t_x = coord->x;
	coord->x = t_x * cos(rt->fTheta) + coord->y * sin(rt->fTheta);
	coord->y = t_x * -sin(rt->fTheta) + coord->y * cos(rt->fTheta);
}
