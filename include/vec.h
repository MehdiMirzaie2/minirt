#ifndef VEC_H
# define VEC_H

typedef struct s_vec2d	t_vec2d;
typedef struct s_vec3d	t_vec3d;
typedef struct s_mat4x4	t_mat4x4;

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
	};
};

struct s_mat4x4
{
    float m[4][4];
};

#endif