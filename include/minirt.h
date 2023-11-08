#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "map.h"
#include <stdio.h>
# include "map.h"
#include <stdio.h>
#include <math.h>

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

typedef struct vec2d
{
	float x, y;
} vec2d;

typedef struct
{
    float x, y, z;
} vec3d;

typedef struct
{
    vec3d p[3];
} triangle;

typedef struct
{
    triangle* tris;
	int num_triangles;
} mesh;

typedef struct
{
    float m[4][4];
} mat4x4;

typedef struct s_rt
{
	t_map	*map;
	void	*mlx;
	void	*window;
	void	*image;
	void	*pointer_to_image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		x_ref;
	int		y_ref;
	vec2d	camera;
	// double	z;
	float	offset_x;
	float	offset_y;
	float	zoom;
	vec3d	light_dir;
	int		color;
	float	fTheta;
	mat4x4	*matProj;
	mesh 	meshCube;
}			t_rt;

typedef struct s_color
{
	double	r;
	double	b;
	double	g;
}	t_color;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	cap1;
	t_vec3	cap2;
	t_vec3	normal;
	double	radius;
	double	height;
	t_color	color;
}	t_cylinder;

// src/init.c
void	init_rt(t_rt *rt);
void	init_mlx(t_rt *rt);
triangle	*init_cube(void);
mat4x4	*init_matProj(void);
int	exit_mlx(t_rt *rt);

// src/keys.c
int	key_hook(int keycode, t_rt *rt);
void	mouse_hook(int mousecode, int x, int y, t_rt *rt);
// int mlx_mouse_hook(rt->window, mouse_hook, rt);
void	mouse_move(int mousecode, int x, int y, t_rt *rt);
void	update_light_dir(vec3d	*light_dir, int x, int y);


// src/line.c
void draw_line(t_rt *rt, vec2d p1, vec2d p2, int color);

// src/triangle.c
void	draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);
void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3);

// src/main.c
void loop(t_rt *rt);
void	clearScreen(t_rt *rt);
int draw(t_rt *rt);
void	put_color_to_pixel(t_rt *rt, int x, int y, int color);

#endif
