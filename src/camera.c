#include "minirt.h"

t_camera	init_camera(void)
{
	return ((t_camera){45.0f, 0.1f, 100.0f});
}

bool	on_update(float ts);
void	on_resize(uint32_t width, uint32_t height);

t_mat4	get_projection(void)
{
	t_mat4	*m_projection;
	int		i;
	
	m_projection = malloc(sizeof(t_mat4));
	i = -1;
	while (++i < 4)
		m_projection->m[i][i] = 1.0f;
	return (*m_projection);
}

t_mat4	get_inverse_projection(void)
{
	t_mat4	*m_inverse_projection;
	int		i;
	
	m_inverse_projection = malloc(sizeof(t_mat4));
	i = -1;
	while (++i < 4)
		m_inverse_projection->m[i][i] = 1.0f;
	return (*m_inverse_projection);
}

t_mat4	get_view(void)
{
	t_mat4	*m_view;
	int		i;
	
	m_view = malloc(sizeof(t_mat4));
	i = -1;
	while (++i < 4)
		m_view->m[i][i] = 1.0f;
	return (*m_view);
}

t_mat4	get_inverse_view(void)
{
	t_mat4	*m_inverse_view;
	int		i;
	
	m_inverse_view = malloc(sizeof(t_mat4));
	i = -1;
	while (++i < 4)
		m_inverse_view->m[i][i] = 1.0f;
	return (*m_inverse_view);
}

vec3d	get_position(void)
{
	return ((vec3d){0.0f, 0.0f, 0.0f});
}

vec3d	get_direction(void)
{
	return ((vec3d){0.0f, 0.0f, 0.0f});
}

vec3d	get_ray_directions(void);

float	get_rotation_speed(void);

void	recalculate_projection(void);
void	recalculate_view(void);
void	recalculate_ray_directions(void);
