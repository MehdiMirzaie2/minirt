#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"

t_camera	*camera(void);
void		set_camera(t_map map);
t_mat4x4	create_matrix(t_vec3d axis, float angle);
t_mat4x4	rotate_camera(void);

#endif
