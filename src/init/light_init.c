/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:38:12 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/01 19:16:58 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_a_light	*a_light(void)
{
	static t_a_light	a_light;

	return (&a_light);
}

void	set_a_light(t_nothitable map)
{
	a_light()->intensity = map.light;
	a_light()->color.r = map.rgb.r;
	a_light()->color.g = map.rgb.g;
	a_light()->color.b = map.rgb.b;
}

t_light	*light(void)
{
	static t_light	light;

	return (&light);
}

void	set_light(t_nothitable map)
{
	light()->pos.x = map.point.x;
	light()->pos.y = map.point.y;
	light()->pos.z = map.point.z;
	light()->intensity = map.brightness;
	light()->color.r = map.rgb.r;
	light()->color.g = map.rgb.g;
	light()->color.b = map.rgb.b;
}
