/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:49:30 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/06 10:55:04 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook_conditions(int keycode, t_rt *rt)
{
	if (keycode == UP)
		camera()->pos.z -= 0.2f;
	else if (keycode == DOWN)
		camera()->pos.z += 0.2f;
	else if (keycode == LEFT)
		camera()->pos.x -= 0.2f;
	else if (keycode == RIGHT)
		camera()->pos.x += 0.2f;
	else if (keycode == W)
		camera()->pos.y -= 0.2f;
	else if (keycode == S)
		camera()->pos.y += 0.2f;
	else if (keycode == D)
		camera()->dir.x += 0.2f;
	else if (keycode == A)
		camera()->dir.x -= 0.2f;
	else if (keycode == Z)
		camera()->dir.y += 0.2f;
	else if (keycode == X)
		camera()->dir.y -= 0.2f;
	else if (keycode == V)
		camera()->dir.z -= 1.0f;
	else if (keycode == ESC)
		exit_mlx(rt);
}

int	key_hook(int keycode, t_rt *rt)
{
	key_hook_conditions(keycode, rt);
	rt->frameindex = 1;
	render(rt);
	return (0);
}
