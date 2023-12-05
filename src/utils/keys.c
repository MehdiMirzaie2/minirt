/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:49:30 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 14:34:23 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == UP)
		camera()->pos.z -= 0.3f;
	else if (keycode == DOWN)
		camera()->pos.z += 0.3f;
	else if (keycode == LEFT)
		camera()->pos.x -= 0.3f;
	else if (keycode == RIGHT)
		camera()->pos.x += 0.3f;
	else if (keycode == W)
		camera()->pos.y -= 0.3f;
	else if (keycode == S)
		camera()->pos.y += 0.3f;
	else if (keycode == D)
		camera()->dir.x += 0.3f;
	else if (keycode == A)
		camera()->dir.x -= 0.3f;
	else if (keycode == C)
		camera()->dir.z += 0.3f;
	else if (keycode == V)
		camera()->dir.z -= 0.3f;
	else if (keycode == ESC)
		exit_mlx(rt);
	rt->frameindex = 1;
	render(rt);
	return (0);
}
