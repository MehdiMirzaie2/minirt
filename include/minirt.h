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
#include "vec3.h"
#include "camera.h"
#include "viewport.h"

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

// PI
# define PI 3.1415926

// src/utils.c
float	max(float arg1, float arg2);
uint32_t	ConvertToRGBA(const t_vec3 color);
float	set_fov(float degrees);
t_vec3	mult_mtrx_vector(t_mat4 *matrix, t_vec3 vector);

// src/init.c
void	init_rt(t_rt *rt);
void	init_mlx(t_rt *rt);
//triangle	*init_cube(void);
t_mat4	*init_matProj(void);
int		exit_mlx(t_rt *rt);

// src/keys.c
int		key_hook(int keycode, t_rt *rt);
void	mouse_hook(int mousecode, int x, int y, t_rt *rt);
void	mouse_move(int mousecode, int x, int y, t_rt *rt);
void	update_light_dir(t_vec3	*light_dir, int x, int y);

// src/parse.c
int		parse(t_map **map, char	*fname);

// src/shapes.c
int		ft_cone(t_rt *rt, t_vec3 coord, t_vec2 notnorm);
int		ft_sphere(t_rt *rt, t_vec2 coord, t_vec2 notnorm);

// src/line.c
void 	draw_line(t_rt *rt, t_vec2 p1, t_vec2 p2, int color);

// src/triangle.c
void	draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);
void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);

// src/main.c

void 	render(t_rt *rt);
void	clearScreen(t_rt *rt);
int 	draw(t_rt *rt);

void	put_color_to_pixel(t_rt *rt, int x, int y, int color);

#endif
