/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:27:32 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/27 12:12:40 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	int				type;
	float			point[3];
	float			light;
	int				rgb[3];
	float			normalized[3];
	int				fov;
	float			brightness;
	float			diameter;
	float			height;
	struct s_map	*next;
} t_map;

enum	e_identifier
{
	E_TTSP = 'S' + 'P',
	E_TTPL = 'p' + 'l',
	E_TTCY = 'c' + 'y',
};

int	parse(t_map **map, char	*fname);

// typedef struct s_map_line
// {
// 	char				*line;
// 	struct	s_map_line	*next;
// } t_map_line;

#endif