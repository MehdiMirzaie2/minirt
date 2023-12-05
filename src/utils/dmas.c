/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmas.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:54:22 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 13:55:10 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d	t_vec3d_div(t_vec3d v1, float deno)
{
	t_vec3d	result;

	result.x = v1.x / deno;
	result.y = v1.y / deno;
	result.z = v1.z / deno;
	return (result);
}

t_vec3d	t_vec3d_scale(t_vec3d v1, float scalar)
{
	t_vec3d	result;

	result.x = v1.x * scalar;
	result.y = v1.y * scalar;
	result.z = v1.z * scalar;
	return (result);
}

t_vec3d	t_vec3d_add(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec3d	t_vec3d_sub(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}
