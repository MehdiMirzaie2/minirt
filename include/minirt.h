#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "map.h"

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
	double	x;
	double	y;
	double	z;
	double	offset_x;
	double	offset_y;
	double	zoom;
	int		color;
	float	fElapsedTime;
}			t_rt;

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


// src/init.c
void	init_rt(t_rt *rt);
void	init_mlx(t_rt *rt);

int main(void);
// void draw(t_rt *rt, mat4x4 matProj, mesh meshCube);

// src/keys.c
int	key_hook(int keycode, t_rt *rt);

#endif
