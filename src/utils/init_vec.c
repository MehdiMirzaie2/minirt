#include "rt.h"

t_vec3d init_vec3d(float x, float y, float z)
{
    t_vec3d point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

t_vec2d init_vec2d(float x, float y)
{
    t_vec2d point;

    point.x = x;
    point.y = y;
    return (point);
}