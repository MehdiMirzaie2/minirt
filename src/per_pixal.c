#include "rt.h"
#include "minirt.h"
#include "structs.h"


t_hitpayload Miss(const t_ray ray)
{
	t_hitpayload payload;
	payload.hit_distance = -1.0f;
	return payload;
}

t_hitpayload ClosestHit(const t_ray ray, float hitDistance, t_map obj)
{
	t_hitpayload payload;
	t_vec3d origin =  t_vec3d_sub(ray.orig, obj.point);

	payload.hit_distance = hitDistance;
	payload.obj = &obj;
	payload.world_positoin = t_vec3d_add(origin, t_vec3d_scale(ray.dir, hitDistance));
	payload.world_normal = payload.world_positoin;
	normalize(&payload.world_normal);
	payload.world_positoin = t_vec3d_add(payload.world_positoin, obj.point);
	return (payload);
}

t_hitpayload TraceRay(t_map *map, t_ray ray)
{
	t_map   *ref_map = map;
	t_map	*closest_obj = NULL;
	float   closest_t_val;
	float   old_closest = __FLT_MAX__;
	t_vec2d point;

	while (ref_map)
	{
		if (ref_map->type == E_TTSP)
			closest_t_val = ft_sphere(ref_map, ray);
		else if (ref_map->type == E_TTCY)
			closest_t_val = ft_cylinder(ref_map, ray);
		else if (ref_map->type == E_TTPL)
			closest_t_val = plane(ref_map, ray);
		if (closest_t_val < old_closest)
		{
			old_closest = closest_t_val;
			closest_obj = ref_map;
		}
		ref_map = ref_map->next;
	}
	if (closest_obj == NULL)
		return Miss(ray);
	return ClosestHit(ray, old_closest, *closest_obj);
}

t_vec3d	per_pixal(t_rt *rt, uint32_t x, uint32_t y)
{
	t_ray ray;
	ray.orig = camera()->pos;
	ray.dir = init_vec3d((float)x, (float)y, -1.0f);
	ray.dir.x /= (float)SIZE;
	ray.dir.y /= (float)SIZE;
	ray.dir.x = ray.dir.x * 2.0f - 1.0f;
	ray.dir.y = ray.dir.y * 2.0f - 1.0f;
	ray.dir.z = -1.0f;

	t_vec3d colour = init_vec3d(0.0f, 0.0f, 0.0f);
	float	multiplier = 1.0f;

	int bounces = 2;
	for (int i = 0; i < bounces; i++)
	{
		t_hitpayload payload = TraceRay(rt->map, ray);
		if (payload.hit_distance < 0.0f || payload.obj->type == E_TTPL)
		{
			// t_vec3d skyColor = init_vec3d(0.0f, 0.0f, 0.0f);
			t_vec3d skyColor = payload.obj->rgb;
			colour = t_vec3d_add(colour, t_vec3d_scale(skyColor, multiplier));
			break ;
		}
		t_vec3d lightDir = init_vec3d(-1, -1, -1);
		normalize(&lightDir);
		// normalize(&(t_vec3d){-1, -1, -1});
		float lightIntensity = max(dot(payload.world_normal, t_vec3d_scale(lightDir, -1)), 0.0f);
		t_vec3d sphereColor = payload.obj->rgb;
		sphereColor = t_vec3d_scale(sphereColor, lightIntensity);
		colour = t_vec3d_add(colour, t_vec3d_scale(sphereColor, multiplier));

		multiplier *= 0.7f;

		ray.orig = t_vec3d_add(payload.world_positoin, t_vec3d_scale(payload.world_normal, 0.0001f));
		ray.dir = cross(ray.dir, payload.world_normal);
	}
	return (colour);
}
