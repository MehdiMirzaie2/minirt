#include "minirt.h"

t_hitpayload	miss(const t_ray ray)
{
	(void)ray;
	t_hitpayload	payload;

	// payload = malloc(sizeof(t_hitpayload));
	payload.hit_distance = -1.0f;
	return (payload);
}

t_hitpayload	closest_hit(const t_ray ray, float hit_distance, t_hitable *obj)
{
	t_hitpayload	payload;
	t_vec3d			origin;

	// payload = malloc(sizeof(t_hitpayload));
	origin = t_vec3d_sub(ray.orig, obj->point);
	payload.raydir = t_vec3d_scale(ray.dir, hit_distance);
	payload.hit_distance = hit_distance;
	payload.obj = obj;

	payload.world_positoin = t_vec3d_add(origin, payload.raydir);
	payload.world_normal = payload.world_positoin;
	normalize(&payload.world_normal);
	payload.world_positoin = t_vec3d_add(payload.world_positoin, obj->point);
	return (payload);
}

t_hitpayload	trace_ray(t_hitable *map, t_ray ray)
{
	t_hitable	*ref_map;
	t_hitable	*closest_obj;
	float	closest_t_val;
	float	old_closest;

	ref_map = map;
	closest_obj = NULL;
	old_closest = __FLT_MAX__;
	while (ref_map)
	{
		if (ref_map->type == SP)
			closest_t_val = ft_sphere(ref_map, ray);
		else if (ref_map->type == CY)
			closest_t_val = ft_cylinder(ref_map, ray);
		else if (ref_map->type == PL)
			closest_t_val = plane(ref_map, ray);
		else if (ref_map->type == CN)
			closest_t_val = ft_cone(ref_map, ray);
		if (closest_t_val < old_closest)
		{
			old_closest = closest_t_val;
			closest_obj = ref_map;
		}
		ref_map = ref_map->next;
	}
	if (closest_obj == NULL)
		return miss(ray);
	return closest_hit(ray, old_closest, closest_obj);
}

// Reflection=Incident−2×(Normal⋅Incident)×Normal
t_vec3d	reflect(t_vec3d incident, t_vec3d normal)
{
    return (t_vec3d_sub(incident, \
		t_vec3d_scale(normal, 2.0f * dot(incident, normal))));
}

t_vec3d	getrendomvec3d(float roughness)
{
	t_vec3d ran_vec;
// int random_number = 1 + rand() % 10
	ran_vec.x = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.y = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.z = ((float)rand() / RAND_MAX - 0.5) * roughness;
	return (ran_vec);
}

// t_ray	set_ray(uint32_t x, uint32_t y)
// {
// 	t_ray	ray;

// 	ray.orig = camera()->pos;
// 	ray.dir = init_vec3d((float)x, (float)y, -1.0f);
// 	ray.dir.x /= (float)SIZE;
// 	ray.dir.y /= (float)SIZE;
// 	ray.dir.x = ray.dir.x * 2.0f - 1.0f;
// 	ray.dir.y = ray.dir.y * 2.0f - 1.0f;
// 	ray.dir.z = -1.0f;
// 	ray.dir = dir_from_mat(&camera()->mat, ray.dir);
// 	normalize(&ray.dir);
// 	return (ray);
// }

void	set_raydir(t_vec3d *raydir)
{
	t_vec2d	ndc_space;
	t_vec2d screen_space;
	t_vec2d camera_space;
	const float	ar = SIZE / SIZE;

	ndc_space.x = ((raydir->x + 0.5f) / SIZE);
	ndc_space.y = ((raydir->y + 0.5f) / SIZE);
	screen_space.x = 2 * ndc_space.x - 1;
	screen_space.y = 2 * ndc_space.y - 1;
	screen_space.y = 1 - 2 * ndc_space.y;
	camera_space.x = (2 * screen_space.x - 1) * ar * (1 / tan(camera()->fov / 2));
	camera_space.y = (1 - 2 * screen_space.y) * (1 / tan(camera()->fov / 2));
	raydir->x = camera_space.x;
	raydir->y = camera_space.y;
	// raydir->z = -1;
}

t_ray	set_ray(uint32_t x, uint32_t y)
{
	t_ray	ray;

	ray.orig = camera()->pos;
	ray.dir = init_vec3d((float)x, (float)y, -1.0f);
	set_raydir(&ray.dir);
	// ray.dir.x /= (float)SIZE;
	// ray.dir.y /= (float)SIZE;
	// ray.dir.x = ray.dir.x * 2.0f - 1.0f;
	// ray.dir.y = ray.dir.y * 2.0f - 1.0f;
	// ray.dir.z = -1.0f;
	ray.dir = dir_from_mat(&camera()->mat, ray.dir);
	normalize(&ray.dir);
	return (ray);
}

t_vec3d	per_pixal(t_rt *rt, uint32_t x, uint32_t y)
{
	t_ray			ray;
	t_vec3d			colour;
	t_vec3d			final_colour;
	float			multiplier;
	int				bounces;
	int				i;
	t_hitpayload	payload;

	ray = set_ray(x, y);
	colour = mincolour;
	final_colour = mincolour;
	multiplier = 1.0f;
	bounces = 5;
	i = -1;
	while (++i < bounces)
	{
		payload = trace_ray(rt->hitable, ray);
		if (payload.hit_distance < 0.0f)
		{
			// t_vec3d skyColor = (t_vec3d){0.0f, 0.0f, 0.0f};
			if (i != 0)
				final_colour = t_vec3d_add(final_colour, t_vec3d_scale(mincolour, multiplier));
			break ;
		}
		colour = color_multiply(payload.obj->rgb, set_light_ratio(rt, &payload));
		final_colour = t_vec3d_add(final_colour, t_vec3d_scale(colour, multiplier));
		multiplier *= 0.5f;
		ray.orig = t_vec3d_add(payload.world_positoin, t_vec3d_scale(payload.world_normal, 0.0001f));
		//t_vec3d randomised = getrendomvec3d(0.1);
		ray.dir = reflect(ray.dir, t_vec3d_add(payload.world_normal, getrendomvec3d(payload.obj->roughness)));
	}
	return (final_colour);
}






























// t_hitpayload	*miss(const t_ray ray)
// {
// 	t_hitpayload	*payload;

// 	payload = malloc(sizeof(t_hitpayload));
// 	payload->hit_distance = -1.0f;
// 	return (payload);
// }

// t_hitpayload	*closest_hit(const t_ray ray, float hit_distance, t_hitable *obj)
// {
// 	t_hitpayload	*payload;
// 	t_vec3d			origin;

// 	payload = malloc(sizeof(t_hitpayload));
// 	origin = t_vec3d_sub(ray.orig, obj->point);
// 	payload->raydir = t_vec3d_scale(ray.dir, hit_distance);
// 	payload->hit_distance = hit_distance;
// 	payload->obj = obj;

// 	payload->world_positoin = t_vec3d_add(origin, payload->raydir);
// 	payload->world_normal = payload->world_positoin;
// 	normalize(&payload->world_normal);
// 	payload->world_positoin = t_vec3d_add(payload->world_positoin, obj->point);
// 	return (payload);
// }

// t_hitpayload	*trace_ray(t_hitable *map, t_ray ray)
// {
// 	t_hitable	*ref_map;
// 	t_hitable	*closest_obj;
// 	float	closest_t_val;
// 	float	old_closest;
// 	t_vec2d	point;

// 	ref_map = map;
// 	closest_obj = NULL;
// 	old_closest = __FLT_MAX__;
// 	while (ref_map)
// 	{
// 		if (ref_map->type == SP)
// 			closest_t_val = ft_sphere(ref_map, ray);
// 		else if (ref_map->type == CY)
// 			closest_t_val = ft_cylinder(ref_map, ray);
// 		else if (ref_map->type == PL)
// 			closest_t_val = plane(ref_map, ray);
// 		if (closest_t_val < old_closest)
// 		{
// 			old_closest = closest_t_val;
// 			closest_obj = ref_map;
// 		}
// 		ref_map = ref_map->next;
// 	}
// 	if (closest_obj == NULL)
// 		return miss(ray);
// 	return closest_hit(ray, old_closest, closest_obj);
// }

// // Reflection=Incident−2×(Normal⋅Incident)×Normal
// t_vec3d	reflect(t_vec3d incident, t_vec3d normal)
// {
//     return (t_vec3d_sub(incident, \
// 		t_vec3d_scale(normal, 2.0f * dot(incident, normal))));
// }

// t_vec3d	getrendomvec3d(float roughness)
// {
// 	t_vec3d ran_vec;
// // int random_number = 1 + rand() % 10
// 	ran_vec.x = ((float)rand() / RAND_MAX - 0.5) * roughness;
// 	ran_vec.y = ((float)rand() / RAND_MAX - 0.5) * roughness;
// 	ran_vec.z = ((float)rand() / RAND_MAX - 0.5) * roughness;
// 	return (ran_vec);
// }

// t_ray	set_ray(uint32_t x, uint32_t y)
// {
// 	t_ray	ray;

// 	ray.orig = camera()->pos;
// 	ray.dir = init_vec3d((float)x, (float)y, -1.0f);
// 	ray.dir.x /= (float)SIZE;
// 	ray.dir.y /= (float)SIZE;
// 	ray.dir.x = ray.dir.x * 2.0f - 1.0f;
// 	ray.dir.y = ray.dir.y * 2.0f - 1.0f;
// 	ray.dir.z = -1.0f;
// 	ray.dir = dir_from_mat(&camera()->mat, ray.dir);
// 	return (ray);
// }

// t_vec3d	per_pixal(t_rt *rt, uint32_t x, uint32_t y)
// {
// 	t_ray			ray;
// 	t_vec3d			colour;
// 	t_vec3d			final_colour;
// 	float			multiplier;
// 	int				bounces;
// 	int				i;
// 	t_hitpayload	*payload;

// 	ray = set_ray(x, y);
// 	colour = (t_vec3d){0,0,0};
// 	final_colour = (t_vec3d){0,0,0};
// 	multiplier = 1.0f;
// 	bounces = 5;
// 	i = -1;
// 	while (++i < bounces)
// 	{
// 		payload = trace_ray(rt->hitable, ray);
// 		if (payload->hit_distance < 0.0f)
// 		{
// 			//t_vec3d skyColor = (t_vec3d){0.0f, 0.0f, 0.0f};
// 			final_colour = t_vec3d_add(final_colour, t_vec3d_scale((t_vec3d){0.0f, 0.0f, 0.0f}, multiplier));
// 			break ;
// 		}
// 		colour = color_multiply(payload->obj->rgb, set_light_ratio(rt, payload));
// 		final_colour = t_vec3d_add(final_colour, t_vec3d_scale(colour, multiplier));
// 		multiplier *= 0.5f;
// 		ray.orig = t_vec3d_add(payload->world_positoin, t_vec3d_scale(payload->world_normal, 0.0001f));
// 		//t_vec3d randomised = getrendomvec3d(0.1);
// 		ray.dir = reflect(ray.dir, t_vec3d_add(payload->world_normal, getrendomvec3d(payload->obj->roughness)));
// 	}
// 	return (final_colour);
// }
