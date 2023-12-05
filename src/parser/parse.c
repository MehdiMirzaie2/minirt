/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:40:01 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/05 12:36:00 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int32_t get_type(char *line, uint32_t *type)
{
	int index;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (!line[index])
		return (-1);
	*type = line[index];
	if (!ft_isspace(line[++index]))
		*type *= line[index];
	if (!ft_isspace(line[index]))
		++index;
	++index;
	return (index);
}

int	init_nothitable(uint32_t type, char *line)
{
	t_nothitable obj;

	obj.type = type;
	if (obj.type == 'L')
	{
		sscanf(line, "%f,%f,%f %f %f,%f,%f", &obj.point.x, &obj.point.y,
			&obj.point.z, &obj.brightness, &obj.rgb.r, &obj.rgb.g, &obj.rgb.b);
		set_light(obj);
	}
	if (obj.type == 'A')
	{
		sscanf(line, "%f %f,%f,%f", &obj.light, &obj.rgb.r, &obj.rgb.g, &obj.rgb.b);
		set_a_light(obj);
	}
	if (obj.type == 'C')
	{
		sscanf(line, "%f,%f,%f %f,%f,%f %d", &obj.point.x, &obj.point.y,
			&obj.point.z, &obj.normalized.x, &obj.normalized.y, &obj.normalized.z, &obj.fov);
		set_camera(obj);
	}
	return (0);
}

int get_hitable(t_hitable **hitable, char *line, uint32_t type)
{
    t_hitable *new = malloc(sizeof(t_hitable));

    if (!new)
        return -1;
    new->type = type;
    new->next = NULL;

    if (*hitable == NULL)
        *hitable = new;
    else
    {
        t_hitable *current = *hitable;
        while (current->next != NULL)
            current = current->next;
        current->next = new;
    }
	if (new->type == SP)
		sscanf(line, "%f,%f,%f %f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->diameter, &new->rgb.r, &new->rgb.g, &new->rgb.b, &new->roughness);
	else if (new->type == PL)
		sscanf(line, "%f,%f,%f %f,%f,%f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->normalized.x, &new->normalized.y, &new->normalized.z, &new->rgb.r, &new->rgb.g, &new->rgb.b, &new->roughness);
	else if (new->type == CY)
		sscanf(line, "%f,%f,%f %f,%f,%f %f %f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->normalized.x, &new->normalized.y, &new->normalized.z, &new->diameter, &new->height, &new->rgb.r, &new->rgb.g, &new->rgb.b, &new->roughness);
	else if (new->type == CN)
		sscanf(line, "%f,%f,%f %f,%f,%f %f", &new->point.x, &new->point.y,
			&new->point.z, &new->rgb.r, &new->rgb.g, &new->rgb.b, &new->roughness);
    return 0;
}


int	parse(t_hitable **hitable, char	*fname)
{
	const int		fd = open(fname, O_RDONLY, 0644);
	char			*line;
	t_hitable		*hitable_ref;
	uint32_t		type;
	int				index;

	if (fd < 0)
		exit(1);
	hitable_ref = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			index = get_type(line, &type);
			if (type == SP || type == CY || type == PL)
				get_hitable(&hitable_ref, &line[index], type);
			else if (type == 'A' || type == 'L' || type == 'C')
				init_nothitable(type, &line[index]);
			free(line);
			line = get_next_line(fd);
		}
	}
	*hitable = hitable_ref;
	return (0);
}
