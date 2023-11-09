
#include "minirt.h"

void normalize(vec3d *vec)
{
    float length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);

    if (length != 0.0f)
    {
        vec->x /= length;
        vec->y /= length;
        vec->z /= length;
    }
}

vec3d vec3d_scale(vec3d v1, float scalar)
{
    vec3d result;

    result.x = v1.x * scalar;
    result.y = v1.y * scalar;
    result.z = v1.z * scalar;
    return (result);
}

vec3d vec3d_add(vec3d v1, vec3d v2)
{
    vec3d result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return (result);
}

float dot(vec3d v1, vec3d v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

uint32_t ConvertToRGBA(const vec3d color)
{
    uint8_t r = (uint8_t)(color.x * 255.0f);
    uint8_t g = (uint8_t)(color.y * 255.0f);
    uint8_t b = (uint8_t)(color.z * 255.0f);

    uint32_t result = (0x00 << 24) | (r << 16) | (g << 8) | b;
    return result;
}

float max(float arg1, float arg2)
{
    if (arg1 < arg2)
        return (arg2);
    return (arg1);
}
