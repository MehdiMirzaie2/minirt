/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:40:01 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/06 09:17:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_nothitable(uint32_t type, char *line)
{
	t_nothitable	obj;

	obj.type = type;
	if (obj.type == 'L')
	{
		sscanf(line, "%f,%f,%f %f %f,%f,%f", &obj.point.x, &obj.point.y,
			&obj.point.z, &obj.brightness, &obj.rgb.r, &obj.rgb.g, &obj.rgb.b);
		set_light(obj);
	}
	if (obj.type == 'A')
	{
		sscanf(line, "%f %f,%f,%f", &obj.light, &obj.rgb.r, &obj.rgb.g, \
			&obj.rgb.b);
		set_a_light(obj);
	}
	if (obj.type == 'C')
	{
		sscanf(line, "%f,%f,%f %f,%f,%f %d", &obj.point.x, &obj.point.y,
			&obj.point.z, &obj.normalized.x, &obj.normalized.y, \
			&obj.normalized.z, &obj.fov);
		set_camera(obj);
	}
	return (0);
}

void	get_hitable_helper2(t_hitable *new, char *line)
{
	if (new->type == SP)
		sscanf(line, "%f,%f,%f %f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->radius2, &new->rgb.r, &new->rgb.g,
			&new->rgb.b, &new->roughness);
	else if (new->type == PL)
		sscanf(line, "%f,%f,%f %f,%f,%f %f,%f,%f %f",
			&new->point.x, &new->point.y, &new->point.z,
			&new->normalized.x, &new->normalized.y, &new->normalized.z,
			&new->rgb.r, &new->rgb.g, &new->rgb.b, &new->roughness);
	else if (new->type == CY)
		sscanf(line, "%f,%f,%f %f,%f,%f %f %f %f,%f,%f %f",
			&new->point.x, &new->point.y, &new->point.z,
			&new->normalized.x, &new->normalized.y, &new->normalized.z,
			&new->radius2, &new->height, &new->rgb.r, &new->rgb.g,
			&new->rgb.b, &new->roughness);
	else if (new->type == CN)
		sscanf(line, "%f,%f,%f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->rgb.r, &new->rgb.g, &new->rgb.b,
			&new->roughness);
}

int	get_hitable(t_hitable **hitable, char *line, uint32_t type)
{
	t_hitable	*new;

	new = get_hitable_helper(hitable, type);
	if (!new)
		return (-1);
	get_hitable_helper2(new, line);
	if (new->type == SP || new->type == CY)
	{
		new->radius2 /= 2.0f;
		new->radius2 = new->radius2 * new->radius2;
	}
	return (0);
}

int	parse(t_hitable **hitable, char	*fname)
{
	int			fd;
	char		*line;
	t_hitable	*hitable_ref;
	uint32_t	type;
	int			index;

	fd = open_helper(fname);
	line = get_next_line(fd);
	hitable_ref = NULL;
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			index = get_type(line, &type);
			if (type == SP || type == CY || type == PL)
				get_hitable(&hitable_ref, &line[index], type);
			else if (type == 'A' || type == 'L' || type == 'C')
				init_nothitable(type, &line[index]);
		}
		free(line);
		line = get_next_line(fd);
	}
	*hitable = hitable_ref;
	return (0);
}
