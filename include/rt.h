#ifndef RT_H
#define RT_H

# define SIZE 700

typedef struct s_rt	t_rt;
typedef struct s_map t_map;
typedef struct s_hitable t_hitable;
typedef struct s_nothitable t_nothitable;
typedef struct s_vec2d	t_vec2d;
typedef struct s_vec3d	t_vec3d;
typedef struct s_hitable	t_hitable;
typedef struct s_nothitable	t_nothitable;
typedef struct s_mat4x4	t_mat4x4;
typedef struct s_camera t_camera;
typedef struct s_onupdate t_onupdate;

struct s_vec2d
{
	float x, y;
};

struct s_vec3d
{
    union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		struct
		{
			float	aa;
			float	bb;
			float	cc;
		};
	};
};

struct s_mat4x4
{
    float m[4][4];
};

enum	e_identifier
{
	SP = 's' * 'p',
	PL = 'p' * 'l',
	CY = 'c' * 'y',
};

typedef struct s_ray
{
	t_vec3d	orig;
	t_vec3d	dir;
}	t_ray;


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
	float			roughness;
	t_map			*next;
};


struct s_hitable
{
	int				type;
	t_vec3d			point;
	t_vec3d			rgb;
	t_vec3d			normalized;
	float			diameter;
	float			height;
	float			roughness;
	t_hitable		*next;
};

struct s_nothitable
{
	int				type;
	t_vec3d			point;
	t_vec3d			rgb;
	t_vec3d			normalized;
	int				fov;
	float			brightness;
	float			light;
};



struct s_camera
{
	t_vec3d		pos;
	t_vec3d		dir;
	t_vec3d		initial_dir;
	t_mat4x4	mat;
	float	fov;
};

typedef struct	s_a_light
{
	float	intensity;
	t_vec3d	color;
}	t_a_light;

typedef struct s_light
{
	t_vec3d	pos;
	float	intensity;
	t_vec3d	color;
}	t_light;

struct s_onupdate
{
	t_vec2d			oldmousepos;
	t_vec2d			mousepos;
	t_vec2d			delta;
	t_vec3d			m_position;
	t_vec3d			m_forward_dir;
	t_vec3d			m_up_dir;
	t_vec3d			m_right_dir;
};

typedef struct s_hitpayload
{
	t_vec3d	raydir;
	float	hit_distance;
	t_vec3d	world_normal;
	t_vec3d world_positoin;
	t_hitable	*obj;
} t_hitpayload;

struct s_rt
{
	t_map			*map;
	t_hitable		*hitable;
	void			*mlx;
	void			*window;
	void			*image;
	void			*pointer_to_image;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				x;
	int				y;
	int				x_ref;
	int				y_ref;
	float			offset_x;
	float			offset_y;
	float			zoom;
	t_vec3d			light_dir;
	t_vec3d			camera;
	int				color;
	float			fTheta;
	t_mat4x4		*matProj;
	t_vec3d			accum[SIZE * SIZE];
	int		frameindex;
	t_onupdate		on_update
};

void rotate_x(t_vec3d *coord, t_rt *rt);
void rotate_y(t_vec3d *coord, t_rt *rt);
void rotate_z(t_vec3d *coord, t_rt *rt);

#endif
