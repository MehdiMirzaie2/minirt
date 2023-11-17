// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map.h                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/26 12:27:32 by mehdimirzai       #+#    #+#             */
// /*   Updated: 2023/11/16 11:23:38 by mmirzaie         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef MAP_H
// # define MAP_H

// #include "vec.h"

// typedef struct s_map t_map;

// struct s_map
// {
// 	int				type;
// 	t_vec3d			point;
// 	float			light;
// 	t_vec3d			rgb;
// 	t_vec3d			normalized;
// 	int				fov;
// 	float			brightness;
// 	float			diameter;
// 	float			height;
// 	t_map			*next;
// };

// enum	e_identifier
// {
// 	E_TTSP = 's' * 'p',
// 	E_TTPL = 'p' * 'l',
// 	E_TTCY = 'c' * 'y',
// };

// // int	parse(t_map **map, char	*fname);

// #endif