/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:05:26 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/27 11:31:54 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	get_map(t_map *map, char *line)
{
	if (ft_isspace(*line) || *line == '\n')
		return (-1);
	map->type = *line;
	if (!ft_isspace(*(++line)))
		map->type += *line;
	if (!ft_isspace(*line))
		++line;
	if (map->type == 'A')
		sscanf(line, "%f %d,%d,%d", &map->light, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == 'C')
		sscanf(line, "%f,%f,%f %f,%f,%f %d", &map->point[0], &map->point[1],
			&map->point[2], &map->normalized[0], &map->normalized[1], &map->normalized[2], &map->fov);
	if (map->type == 'L')
		sscanf(line, "%f,%f,%f %f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->brightness, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTSP)
		sscanf(line, "%f,%f,%f %f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->diameter, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTPL)
		sscanf(line, "%f,%f,%f %f,%f,%f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->normalized[0], &map->normalized[1], &map->normalized[2], &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTCY)
		sscanf(line, "%f,%f,%f %f,%f,%f %f %f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->normalized[0], &map->normalized[1], &map->normalized[2], &map->diameter, &map->height, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	return (0);
}

int	ft_read(t_map **map, char	*fname)
{
	const int	fd = open(fname, O_RDONLY, 0644);
	char	*line;
	t_map	*map_ref;

	map_ref = *map;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\n')
			line = get_next_line(fd);
		else
		{
			get_map(map_ref, line);
			free(line);
			line = get_next_line(fd);
			if (line != NULL)
			{
				map_ref->next = malloc(sizeof(t_map));
				map = &map_ref->next;
			}
		}
	}
	return (0);
}