
#include "minirt.h"

void normalize(t_vec3d *vec)
{
    float length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);

    if (length != 0.0f)
    {
        vec->x /= length;
        vec->y /= length;
        vec->z /= length;
    }
}

float normalized(t_vec3d vec)
{
    float length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

    if (length != 0.0f)
    {
        vec.x /= length;
        vec.y /= length;
        vec.z /= length;
    }
	return (length);
}

t_vec3d t_vec3d_scale(t_vec3d v1, float scalar)
{
    t_vec3d result;

    result.x = v1.x * scalar;
    result.y = v1.y * scalar;
    result.z = v1.z * scalar;
    return (result);
}

t_vec3d t_vec3d_add(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return (result);
}

t_vec3d t_vec3d_sub(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return (result);
}

float dot(t_vec3d v1, t_vec3d v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

uint32_t ConvertToRGBA(const t_vec3d color)
{
    uint8_t r = (uint8_t)(color.r * 255.0f);
    uint8_t g = (uint8_t)(color.g * 255.0f);
    uint8_t b = (uint8_t)(color.b * 255.0f);

    uint32_t result = (0x00 << 24) | (r << 16) | (g << 8) | b;
    return result;
}

float max(float arg1, float arg2)
{
    if (arg1 < arg2)
        return (arg2);
    return (arg1);
}
