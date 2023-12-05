/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:00:07 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 16:46:02 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// std
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <unistd.h>

// ours
# include "get_next_line.h"
# include "libft.h"
# include "rt.h"

// Srceen dimensions
# define SIZE 700

// KEYCODES
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define W 13
# define S 1
# define D 2
# define A 0
# define C 8
# define V 9
# define J 38
# define I 34
# define D 2

// Initailizes min rgb t_vec3d and max rgb t_vec3d

// MOUSECODES
# define SCROLL_UP 4
# define SCROLL_DOWN 5

t_vec3d			cross(t_vec3d v1, t_vec3d v2);

int				parse(t_hitable **hitable, char	*fname);
int				open_helper(char *fname);
int32_t			get_type(char *line, uint32_t *type);
t_hitable		*get_hitable_helper(t_hitable **hitable, uint32_t type);

// src/utils.c
void			t_vec3dmemset(t_vec3d accum[][SIZE*SIZE], int c);
uint32_t		convert_to_rgba(const t_vec3d color);
float			dot(t_vec3d v1, t_vec3d v2);
void			normalize(t_vec3d *vec);
float			length(t_vec3d vec);
t_vec3d			color_multiply(t_vec3d color, float ratio);
t_vec3d			clamp(t_vec3d value, t_vec3d min, t_vec3d max);

// src/utils/dmas.c
t_vec3d			t_vec3d_add(t_vec3d v1, t_vec3d v2);
t_vec3d			t_vec3d_sub(t_vec3d v1, t_vec3d v2);
t_vec3d			t_vec3d_scale(t_vec3d v1, float scalar);
t_vec3d			t_vec3d_div(t_vec3d v1, float deno);

// src/init.c
void			init_rt(t_rt *rt);
void			init_mlx(t_rt *rt);
int				exit_mlx(t_rt *rt);

// src/keys.c
int				key_hook(int keycode, t_rt *rt);

// src/shapes.c
float			ft_cone(t_hitable *map, t_ray coord);
float			ft_cylinder(t_hitable *map, t_ray dir);
float			plane(t_hitable *map, t_ray dir);
float			ft_sphere(t_hitable *map, t_ray dir);

// src/main.c
void			render(t_rt *rt);
// void			clearScreen(t_rt *rt);
// void			put_color_to_pixel(t_rt *rt, int x, int y, int color);

// init/camera.c
t_camera		*camera(void);
void			set_camera(t_nothitable map);
t_mat4x4		create_matrix(t_vec3d axis, float angle);
t_mat4x4		rotate_camera(void);
t_vec3d			dir_from_mat(t_mat4x4 *mat, t_vec3d v);

// init/light.c
t_a_light		*a_light(void);
void			set_a_light(t_nothitable map);
t_light			*light(void);
void			set_light(t_nothitable map);
float			diffuse_light(t_vec3d norm, t_vec3d light);
float			specular_light(t_vec3d norm, t_vec3d lvec, t_vec3d dir,
					float ratio);
float			set_light_ratio(t_rt *rt, t_hitpayload *payload);

// src/utils/init_vec.c
t_vec3d			init_vec3d(float x, float y, float z);
t_vec2d			init_vec2d(float x, float y);

// src/per_pixel.c
t_vec3d			per_pixal(t_rt *rt, uint32_t x, uint32_t y);
t_hitpayload	trace_ray(t_hitable *map, t_ray ray);

t_vec3d			reflect(t_vec3d incident, t_vec3d normal);
t_vec3d			getrendomvec3d(float roughness);
void			set_raydir(t_vec3d *raydir);
t_ray			set_ray(uint32_t x, uint32_t y);

#endif
