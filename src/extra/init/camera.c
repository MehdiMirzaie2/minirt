#include "minirt.h"

t_camera	*camera(void)
{
	static t_camera	*camera;

	return (&camera);
}

void	set_camera(t_map map)
{
	camera()->pos.x = map.pos.x;
	camera()->pos.y = map.pos.y;
	camera()->pos.z = map.pos.z;
	camera()->dir.x = map.dir.x;
	camera()->dir.y = map.dir.y;
	camera()->dir.z = map.dir.z;
	camera()->initial_dir.x = 0.0;
	camera()->initial_dir.y = 0.0;
	camera()->initial_dir.z = viewport()->dist;
	set_fov(map.fov);
}

t_mat4	create_matrix(t_vec3 axis, float angle)
{
	t_mat4		matrix;
	float		cos_theta;
	float		sin_theta;
	float		one_minus_cos_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	one_minus_cos_theta = 1.0 - cos_theta;
	matrix.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos_theta;
	matrix.m[0][1] = axis.x * axis.y * one_minus_cos_theta - axis.z * sin_theta;
	matrix.m[0][2] = axis.x * axis.z * one_minus_cos_theta + axis.y * sin_theta;
	matrix.m[1][0] = axis.y * axis.x * one_minus_cos_theta + axis.z * sin_theta;
	matrix.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos_theta;
	matrix.m[1][2] = axis.y * axis.z * one_minus_cos_theta - axis.x * sin_theta;
	matrix.m[2][0] = axis.z * axis.x * one_minus_cos_theta - axis.y * sin_theta;
	matrix.m[2][1] = axis.z * axis.y * one_minus_cos_theta + axis.x * sin_theta;
	matrix.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos_theta;
	return (matrix);
}

t_mat4	rotate_camera(void)
{
	t_vec3	axis;
	t_vec3	cross;
	float	angle;
	t_mat4	matrix;

	angle = vec3_angle(camera()->initial_dir, camera()->dir);
	cross = vec3_cross(camera()->initial_dir, camera()->dir);
	axis = cross;
	matrix = create_matrix(axis, angle);
	return (matrix);
}
