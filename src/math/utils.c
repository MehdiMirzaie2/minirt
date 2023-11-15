
#include "minirt.h"

uint32_t ConvertToRGBA(const t_color color)
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

void MultiplyMatrixVector(t_vec3 *i, t_vec3 *o, t_mat4 *m)
{
	o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
	o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
	o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
	float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

	if (w != 0.0f)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}
