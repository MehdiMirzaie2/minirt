#ifndef MINIRT_H
# define MINIRT_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>

#include "libft.h"
#include "get_next_line.h"
#include "structs.h"
#include "map.h"
#include "vec3.h"
#include "camera.h"

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

// src/utils.c
float	max(float arg1, float arg2);
uint32_t ConvertToRGBA(const vec3d color);
float	dot(vec3d v1, vec3d v2);
vec3d	vec3d_add(vec3d v1, vec3d v2);
vec3d	vec3d_scale(vec3d v1, float scalar);
void	normalize(vec3d *vec);

// src/init.c
void	init_rt(t_rt *rt);
void	init_mlx(t_rt *rt);
triangle	*init_cube(void);
t_mat4	*init_matProj(void);
int		exit_mlx(t_rt *rt);

// src/keys.c
int		key_hook(int keycode, t_rt *rt);
void	mouse_hook(int mousecode, int x, int y, t_rt *rt);
void	mouse_move(int mousecode, int x, int y, t_rt *rt);
void	update_light_dir(vec3d	*light_dir, int x, int y);

// src/shapes.c
int		ft_cone(t_rt *rt, vec3d coord, vec2d notnorm);
int		ft_sphere(t_rt *rt, vec2d coord, vec2d notnorm);

// src/line.c
void 	draw_line(t_rt *rt, vec2d p1, vec2d p2, int color);

// src/triangle.c
void	draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);
void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);

// src/main.c

void 	loop(t_rt *rt);
void	clearScreen(t_rt *rt);
int 	draw(t_rt *rt);

void	loop(t_rt *rt);
void	clearScreen(t_rt *rt);
void	put_color_to_pixel(t_rt *rt, int x, int y, int color);

#endif
