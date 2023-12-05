/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:50:23 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 14:43:18 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d	clamp(t_vec3d value, t_vec3d min, t_vec3d max)
{
	t_vec3d	result;

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

void	normalize(t_vec3d *vec)
{
	float	length;

	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length != 0.0f)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
}

float	length(t_vec3d vec)
{
	float	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (length);
}

float	dot(t_vec3d v1, t_vec3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

uint32_t	convert_to_rgba(const t_vec3d color)
{
	uint32_t	result;

	result = ((int)color.r << 16) | ((int)color.g << 8) | (int)color.b;
	return (result);
}
