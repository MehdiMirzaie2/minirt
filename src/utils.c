
#include "minirt.h"

uint32_t ConvertToRGBA(const t_vec3 color)
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

void	set_fov(float degrees)
{
	float	radians;
	float	hipo;
	float	sine;
	float	fov;

	radians = (degrees * (PI / 180)) / 2;
	viewport()->width = (tan(radians) * viewport()->dist) * 2;
	viewport()->height = viewport()->width / viewport()->aspect_ratio;
	hipo = sprt(pow(viewport()->width / 2, 2)) + pow(viewport()->dist, 2);
	sine = (viewport()->width / 2) / hipo;
	fov = (asin(sine) * 2) * 180 / PI;
	return (fov);
}
