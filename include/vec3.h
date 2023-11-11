#ifndef VEC3_H
#define VEC3_H

#include "minirt.h"

t_vec3	vec3_add(t_vec3 v, t_vec3 u);
t_vec3	vec3_sub(t_vec3 v, t_vec3 u);
t_vec3	vec3_scale(t_vec3 v, float t);
t_vec3	vec3_divide(t_vec3 v, float t);

float	vec3_len_squared(t_vec3 v);
float	vec3_len(t_vec3 v);
float	vec3_normalize(t_vec3 v);
t_vec3	vec3_normalized(void);

float	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3	unit_vector(t_vec3 v);

#endif
