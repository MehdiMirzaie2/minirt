#ifndef STRUCTS_H
# define STRUCTS_H

# define t_vec3 t_color

enum	e_identifier
{
	E_TTSP = 's' * 'p',
	E_TTPL = 'p' * 'l',
	E_TTCY = 'c' * 'y',
};

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef struct s_mat4
{
	float	m[4][4];
}	t_mat4;

typedef	struct s_viewport
{
	float	width;
	float	height;
	float	dist;
	float	aspect_ratio;
}	t_viewport;

typedef struct s_map
{
	int				type;
	float			light;
	int				rgb[3];
	t_vec3			pos;
	t_vec3			dir;
	float			fov;
	float			brightness;
	float			diameter;
	float			height;
	struct s_map	*next;
}	t_map;

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
	float	zoom;
	t_vec3	light_dir;
	t_mat4	*matProj;
}	t_rt;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	cap1;
	t_vec3	cap2;
	t_vec3	normal;
	float	radius;
	float	height;
	t_color	color;
}	t_cylinder;

//typedef struct
//{
//	t_vec3 p[3];
//}	triangle;

//typedef struct
//{
//	triangle* tris;
//	int num_triangles;
//}	mesh;

#endif
