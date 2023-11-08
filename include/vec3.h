#ifndef VEC3_H
#define VEC3_H

#include "minirt.h"

vec3d	vec3_add(vec3d v, vec3d u);
vec3d	vec3_sub(vec3d v, vec3d u);
vec3d	vec3_multiply(vec3d v, float t);
vec3d	vec3_divide(vec3d v, float t);

float	vec3_len_squared(vec3d v);
float	vec3_len(vec3d v);
float	vec3_normalize(vec3d v);
vec3d	vec3_normalized(void);

float	vec3_dot(vec3d v1, vec3d v2);
vec3d	vec3_cross(vec3d v1, vec3d v2);
vec3d	unit_vector(vec3d v);

#endif
