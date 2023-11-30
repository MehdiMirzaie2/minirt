#ifndef LIGHT_H
# define LIGHT_H

#include "minirt.h"

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

t_a_light	*a_light(void);
void		set_a_light(t_nothitable map);

t_light		*light(void);
void		set_light(t_nothitable map);

float		diffuse_light(t_vec3d norm, t_vec3d light);
float		specular_light(t_vec3d norm, t_vec3d lvec, t_vec3d dir, float ratio);

#endif
