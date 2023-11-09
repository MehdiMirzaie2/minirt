#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct vec2d
{
	float x, y;
}	vec2d;

typedef struct
{
	float x, y, z, m;
}	vec3d;

typedef struct s_color
{
	float	r;
	float	b;
	float	g;
}	t_color;

typedef struct s_camera
{
	float vertical_fov;
	float near_clip;
	float far_clip;
}	t_camera;

typedef struct
{
	vec3d p[3];
}	triangle;

typedef struct
{
	triangle* tris;
	int num_triangles;
}	mesh;

typedef struct s_mat4
{
	float m[4][4];
}	t_mat4;

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
	vec2d	camera;
	// double	z;
	float	offset_x;
	float	offset_y;
	float	zoom;
	vec3d	light_dir;
	int		color;
	float	fTheta;
	t_mat4	*matProj;
	mesh 	meshCube;
}	t_rt;

typedef struct s_cylinder
{
	vec3d	center;
	vec3d	cap1;
	vec3d	cap2;
	vec3d	normal;
	float	radius;
	float	height;
	t_color	color;
}	t_cylinder;

#endif
