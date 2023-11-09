#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"

t_camera	init_camera(void);

bool	on_update(float ts);
void	on_resize(uint32_t width, uint32_t height);

t_mat4	get_projection(void);
t_mat4	get_inverse_projection(void);
t_mat4	get_view(void);
t_mat4	get_inverse_view(void);

vec3d	get_position(void);
vec3d	get_direction(void);

vec3d	get_ray_directions(void);

float	get_rotation_speed(void);

void	recalculate_projection(void);
void	recalculate_view(void);
void	recalculate_ray_directions(void);

#endif
