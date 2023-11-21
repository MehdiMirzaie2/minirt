#include "minirt.h"

t_camera	*camera(void)
{
	static t_camera	camera;

	return (&camera);
}

void	set_camera(t_map map)
{
	camera()->pos.x = map.point.x;
	camera()->pos.y = map.point.y;
	camera()->pos.z = map.point.z;
	camera()->dir.x = map.normalized.x;
	camera()->dir.y = map.normalized.y;
	camera()->dir.z = map.normalized.z;
	camera()->initial_dir.x = 0.0f;
	camera()->initial_dir.y = 0.0f;
	camera()->initial_dir.z = -1.0f;
	camera()->fov = (float)map.fov;
}

// to get the angle of two vectors using dot prodcut of them.
float	angle_of_two_vec(t_vec3d v1, t_vec3d v2)
{
	float	norm1;
	float	norm2;
	float	dot_product;
	float	radians;

	norm1 = normalized(v1);
	norm2 = normalized(v2);
	dot_product = dot(v1, v2);
	radians = acos(dot_product / (norm1 * norm2));
	return (radians);
}

// to get another vector 90 degreed from the two.
t_vec3d	cross(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_mat4x4	rotate_camera(void)
{
	t_vec3d		axis;
	t_vec3d		cross_product;
	float		angle;
	t_mat4x4	matrix;

	angle = angle_of_two_vec(camera()->initial_dir, camera()->dir);
	cross_product = cross(camera()->initial_dir, camera()->dir);
	axis = cross_product;
	matrix = create_matrix(axis, angle);
	return (matrix);
}

t_mat4x4	create_matrix(t_vec3d axis, float angle)
{
	t_mat4x4	matrix;
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

t_vec3d	dir_from_mat(t_mat4x4 *mat, t_vec3d v)
{
	t_vec3d	result;

	result.x = mat->m[0][0] * v.x + mat->m[0][1] * v.y + mat->m[0][2] * v.z;
	result.y = mat->m[1][0] * v.x + mat->m[1][1] * v.y + mat->m[1][2] * v.z;
	result.z = mat->m[2][0] * v.x + mat->m[2][1] * v.y + mat->m[2][2] * v.z;
	return (result);
}
