/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:05:26 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/08 22:25:50 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_map(t_map *map, char *line)
{
	if (ft_isspace(*line) || *line == '\n')
		return (-1);
	if (!line)
		return (-1);
	map->type = *line;
	printf("line - %s\n", line);
	if (!ft_isspace(*(++line)))
		map->type *= *line;
	if (!ft_isspace(*line))
		++line;
	++line;
	if (map->type == 'A')
		ft_sscanf(line, "%f %d,%d,%d", &map->light, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == 'C')
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %d", &map->point[0], &map->point[1],
			&map->point[2], &map->normalized[0], &map->normalized[1], &map->normalized[2], &map->fov);
	if (map->type == 'L')
		ft_sscanf(line, "%f,%f,%f %f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->brightness, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTSP)
		ft_sscanf(line, "%f,%f,%f %f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->diameter, &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTPL)
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %d,%d,%d", &map->point[0], &map->point[1],
			&map->point[2], &map->normalized[0], &map->normalized[1], &map->normalized[2], &map->rgb[0], &map->rgb[1], &map->rgb[2]);
	if (map->type == E_TTCY)
	{
		ft_sscanf(line, "%f,%f,%f %f,%f,%f %f %f %d,%d,%d", \
			&map->point[0], &map->point[1], &map->point[2], \
			&map->normalized[0], &map->normalized[1], &map->normalized[2], \
			&map->diameter, &map->height, \
			&map->rgb[0], &map->rgb[1], &map->rgb[2]);
		printf("inside parsing map - %f\n", map->point[0]);
		printf("inside parsing map - %f\n", map->point[1]);
		printf("inside parsing map - %f\n", map->point[2]);
	}
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

