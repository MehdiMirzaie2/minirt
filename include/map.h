/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:27:32 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/11/15 12:23:58 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "vec.h"

// typedef struct s_scene		t_scene;
// typedef struct s_amblight	t_amblight;
// typedef struct s_camera		t_camera;
// typedef struct s_light		t_light;
// typedef struct s_sphere		t_sphere;
// typedef struct s_plane		t_plane;
// typedef struct s_cylinder	t_cylinder;

// // Ambient lightning
// struct s_scene
// {
// 	t_amblight		*a_light;
// 	t_camera		*camera;
// 	t_light			*light;
// 	t_sphere		*sphere;
// 	t_plane			*plane;
// 	t_cylinder		*s_cylinder;
// };

// struct a_light
// {
// 	float			light_ratio;
// 	t_vec3d			rgb;
// };

// struct s_camera
// {
// 	t_vec3d			point;
// 	t_vec3d			normalized;
// 	int				fov;
// };

// struct s_light
// {
// 	t_vec3d			point;
// 	float			brightness;
// 	t_vec3d			rgb;
// };

// struct s_sphere
// {
// 	t_vec3d			point;
// 	float			diameter;
// 	t_vec3d			rgb;
// 	t_sphere		*next;
// };

// struct s_plane
// {
// 	t_vec3d			point;
// 	t_vec3d			normal;
// 	t_vec3d			rgb;
// 	t_plane			*next;
// };

// struct s_cylinder
// {
// 	t_vec3d			point;
// 	t_vec3d			normal;
// 	float			diameter;
// 	float			height;
// 	t_vec3d			rgb;
// 	t_cylinder		*next;
// };

// typedef struct s_map
// {
// 	int				type;
// 	float			point[3];
// 	float			light;
// 	int				rgb[3];
// 	float			normalized[3];
// 	int				fov;
// 	float			brightness;
// 	float			diameter;
// 	float			height;
// 	struct s_map	*next;
// } t_map;

typedef struct s_map t_map;

struct s_map
{
	int				type;
	t_vec3d			point;
	float			light;
	t_vec3d			rgb;
	t_vec3d			normalized;
	int				fov;
	float			brightness;
	float			diameter;
	float			height;
	t_map			*next;
};

enum	e_identifier
{
	E_TTSP = 's' * 'p',
	E_TTPL = 'p' * 'l',
	E_TTCY = 'c' * 'y',
};

// int	parse(t_map **map, char	*fname);

#endif