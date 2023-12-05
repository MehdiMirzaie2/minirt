/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:42:25 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/05 12:42:28 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*camera(void)
{
	static t_camera	camera;

	return (&camera);
}

void	set_camera(t_nothitable map)
{
	camera()->pos.x = map.point.x;
	camera()->pos.y = map.point.y;
	camera()->pos.z = map.point.z;
	camera()->dir.x = map.normalized.x;
	camera()->dir.y = map.normalized.y;
	camera()->dir.z = map.normalized.z;
	camera()->initial_dir.x = 0.0f;
	camera()->initial_dir.y = 0.0f;
	camera()->initial_dir.z = -1.0f;
	camera()->fov = (float)map.fov;
}
