/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:05:26 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/16 12:32:27 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "map.h"
#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	get_map(t_map *map, char *line)
{
	if (ft_isspace(*line) || *line == '\n')
		return (-1);
	if (!line)
		return (-1);
	map->type = *line;
	if (!ft_isspace(*(++line)))
		map->type *= *line;
	if (!ft_isspace(*line))
		++line;
	++line;
	if (map->type == 'A')
		ft_sscanf(line, "%f %f,%f,%f", &map->light, &map->rgb.r, &map->rgb.g, &map->rgb.b);
	if (map->type == 'C')
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %d", &map->point.x, &map->point.y,
			&map->point.z, &map->normalized.x, &map->normalized.y, &map->normalized.z, &map->fov);
	if (map->type == 'L')
		ft_sscanf(line, "%f,%f,%f %f %f,%f,%f", &map->point.x, &map->point.y,
			&map->point.z, &map->brightness, &map->rgb.r, &map->rgb.g, &map->rgb.b);
	if (map->type == E_TTSP)
		ft_sscanf(line, "%f,%f,%f %f %f,%f,%f", &map->point.x, &map->point.y,
			&map->point.z, &map->diameter, &map->rgb.r, &map->rgb.g, &map->rgb.b);
	if (map->type == E_TTPL)
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %f,%f,%f", &map->point.x, &map->point.y,
			&map->point.z, &map->normalized.x, &map->normalized.y, &map->normalized.z, &map->rgb.r, &map->rgb.g, &map->rgb.b);
	if (map->type == E_TTCY)
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %f %f %f,%f,%f", &map->point.x, &map->point.y,
			&map->point.z, &map->normalized.x, &map->normalized.y, &map->normalized.z, &map->diameter, &map->height, &map->rgb.r, &map->rgb.g, &map->rgb.b);
	return (0);
}

int	parse(t_map **map, char	*fname)
{
	const int	fd = open(fname, O_RDONLY, 0644);
	char	*line;
	t_map	*map_ref;

	map_ref = map[0];
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
			get_map(map_ref, line);
			free(line);
			line = get_next_line(fd);
			if (line != NULL)
			{
				map_ref->next = malloc(sizeof(t_map));
				map_ref = map_ref->next;
				map_ref->next = NULL;
			}
		}
	}
	return (0);
}

