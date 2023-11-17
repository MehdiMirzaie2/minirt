#ifndef MINIRT_H
#define MINIRT_H

// std
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <math.h>

// ours
#include "rt.h"

// Srceen dimensions
# define SIZE 700

// KEYCODES
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define C 8
# define J 38
# define I 34
# define D 2

// MOUSECODES
# define SCROLL_UP 4
# define SCROLL_DOWN 5

int				parse(t_map **map, char	*fname);
void			test_parser(t_map *map);

// src/utils.c
float			max(float arg1, float arg2);
uint32_t		ConvertToRGBA(const t_vec3d color);
float			dot(t_vec3d v1, t_vec3d v2);
t_vec3d			t_vec3d_add(t_vec3d v1, t_vec3d v2);
t_vec3d			t_vec3d_sub(t_vec3d v1, t_vec3d v2);
t_vec3d			t_vec3d_scale(t_vec3d v1, float scalar);
void			normalize(t_vec3d *vec);

// src/init.c
void			init_rt(t_rt *rt);
void			init_mlx(t_rt *rt);
t_mat4x4		*init_matProj(void);

// src/keys.c
int				key_hook(int keycode, t_rt *rt);
void			mouse_hook(int mousecode, int x, int y, t_rt *rt);
void			mouse_move(int mousecode, int x, int y, t_rt *rt);
void			update_light_dir(t_vec3d	*light_dir, int x, int y);

// src/shapes.c
float			ft_cone(t_map *map, t_vec2d coord, t_vec2d notnorm);
float			ft_cylinder(t_map *map, t_vec2d coord, t_vec2d notnorm);
float 			plane(t_map *map, t_vec2d coord, t_vec2d notnorm);
float			ft_sphere(t_map *map, t_vec2d coord, t_vec2d notnorm);

// src/line.c
void			draw_line(t_rt *rt, t_vec2d p1, t_vec2d p2, int color);

// src/triangle.c
void			draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);
void			draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);

// src/main.c
void			rander(t_rt *rt);
void			clearScreen(t_rt *rt);
void			put_color_to_pixel(t_rt *rt, int x, int y, int color);

#endif