/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:40:01 by jaeshin           #+#    #+#             */
/*   Updated: 2023/12/01 19:10:39 by jaeshin          ###   ########.fr       */
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
	t_nothitable nothitable;

	nothitable.type = type;
	if (nothitable.type == 'L')
	{
		sscanf(line, "%f,%f,%f %f %f,%f,%f", &nothitable.point.x, &nothitable.point.y,
			&nothitable.point.z, &nothitable.brightness, &nothitable.rgb.r, &nothitable.rgb.g, &nothitable.rgb.b);
		set_light(nothitable);
	}
	if (nothitable.type == 'A')
	{
		sscanf(line, "%f %f,%f,%f", &nothitable.light, &nothitable.rgb.r, &nothitable.rgb.g, &nothitable.rgb.b);
		set_a_light(nothitable);
	}
	if (nothitable.type == 'C')
	{
		sscanf(line, "%f,%f,%f %f,%f,%f %d", &nothitable.point.x, &nothitable.point.y,
			&nothitable.point.z, &nothitable.normalized.x, &nothitable.normalized.y, &nothitable.normalized.z, &nothitable.fov);
		set_camera(nothitable);
	}
	return (0);
}

int get_hitable(t_hitable **hitable, char *line, uint32_t type)
{
    t_hitable *new_hitable = malloc(sizeof(t_hitable));

    if (!new_hitable)
    {
        // Handle memory allocation failure
        return -1;
    }

    new_hitable->type = type;
    new_hitable->next = NULL;

    if (*hitable == NULL)
    {
        *hitable = new_hitable;
    }
    else
    {
        t_hitable *current = *hitable;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_hitable;
    }
	if (new_hitable->type == SP)
		sscanf(line, "%f,%f,%f %f %f,%f,%f %f", &new_hitable->point.x, &new_hitable->point.y,
			&new_hitable->point.z, &new_hitable->diameter, &new_hitable->rgb.r, &new_hitable->rgb.g, &new_hitable->rgb.b, &new_hitable->roughness);
	else if (new_hitable->type == PL)
		sscanf(line, "%f,%f,%f %f,%f,%f %f,%f,%f %f", &new_hitable->point.x, &new_hitable->point.y,
			&new_hitable->point.z, &new_hitable->normalized.x, &new_hitable->normalized.y, &new_hitable->normalized.z, &new_hitable->rgb.r, &new_hitable->rgb.g, &new_hitable->rgb.b, &new_hitable->roughness);
	else if (new_hitable->type == CY)
		sscanf(line, "%f,%f,%f %f,%f,%f %f %f %f,%f,%f %f", &new_hitable->point.x, &new_hitable->point.y,
			&new_hitable->point.z, &new_hitable->normalized.x, &new_hitable->normalized.y, &new_hitable->normalized.z, &new_hitable->diameter, &new_hitable->height, &new_hitable->rgb.r, &new_hitable->rgb.g, &new_hitable->rgb.b, &new_hitable->roughness);
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
		return (0);
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
