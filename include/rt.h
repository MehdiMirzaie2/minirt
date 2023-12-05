/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:07:49 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/05 16:55:40 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define SIZE 700

typedef struct s_rt				t_rt;
typedef struct s_ray			t_ray;
typedef struct s_map			t_map;
typedef struct s_hitable		t_hitable;
typedef struct s_nothitable		t_nothitable;
typedef struct s_vec2d			t_vec2d;
typedef struct s_vec3d			t_vec3d;
typedef struct s_hitable		t_hitable;
typedef struct s_nothitable		t_nothitable;
typedef struct s_mat4x4			t_mat4x4;
typedef struct s_camera			t_camera;
typedef struct s_a_light		t_a_light;
typedef struct s_light			t_light;
typedef struct s_hitpayload		t_hitpayload;

struct s_vec2d
{
	union
	{
		struct
		{
			float	x;
			float	y;
		};
		struct
		{
			float	t;
			float	nt;
		};
	};
};

struct s_vec3d
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
		};
		struct
		{
			float	r;
			float	g;
			float	b;
		};
		struct
		{
			float	aa;
			float	bb;
			float	cc;
		};
	};
};

struct	s_mat4x4
{
	float	m[4][4];
};

enum	e_identifier
{
	SP = 's' * 'p',
	PL = 'p' * 'l',
	CY = 'c' * 'y',
	CN = 'c' * 'n',
};

struct s_ray
{
	t_vec3d	orig;
	t_vec3d	dir;
};

struct s_map
{
	int			type;
	t_vec3d		point;
	float		light;
	t_vec3d		rgb;
	t_vec3d		normalized;
	int			fov;
	float		brightness;
	float		diameter;
	float		height;
	float		roughness;
	t_map		*next;
};

struct s_hitable
{
	int				type;
	t_vec3d			point;
	t_vec3d			rgb;
	t_vec3d			normalized;
	float			radius2;
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
	float		fov;
};

struct	s_a_light
{
	float	intensity;
	t_vec3d	color;
};

struct s_light
{
	t_vec3d	pos;
	float	intensity;
	t_vec3d	color;
};

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

struct s_hitpayload
{
	t_vec3d		raydir;
	float		hit_distance;
	t_vec3d		world_normal;
	t_vec3d		world_positoin;
	t_hitable	*obj;
};

struct s_rt
{
	t_hitable		*hitable;
	void			*mlx;
	void			*window;
	void			*image;
	void			*pointer_to_image;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	float			theta;
	t_vec3d			mincolour;
	t_vec3d			maxcolour;
	t_vec3d			accum[SIZE * SIZE];
	int				frameindex;
	int				i;
	float			mul;
};

#endif
