#include "minirt.h"
#include "rt.h"

t_hitpayload *Miss(const t_ray ray)
{
	t_hitpayload *payload = malloc(sizeof(t_hitpayload));
	payload->hit_distance = -1.0f;
	return payload;
}

t_hitpayload *ClosestHit(const t_ray ray, float hitDistance, t_hitable *obj)
{
	t_hitpayload *payload = malloc(sizeof(t_hitpayload));;
	t_vec3d origin =  t_vec3d_sub(ray.orig, obj->point);

	payload->raydir = t_vec3d_scale(ray.dir, hitDistance);
	payload->hit_distance = hitDistance;
	payload->obj = obj;

	payload->world_positoin = t_vec3d_add(origin, payload->raydir);
	payload->world_normal = payload->world_positoin;
	normalize(&payload->world_normal);
	payload->world_positoin = t_vec3d_add(payload->world_positoin, obj->point);
	return (payload);
}

t_hitpayload *TraceRay(t_hitable *map, t_ray ray)
{
	t_hitable   *ref_map = map;
	t_hitable	*closest_obj = NULL;
	float   closest_t_val;
	float   old_closest = __FLT_MAX__;
	t_vec2d point;

	while (ref_map)
	{
		if (ref_map->type == SP)
			closest_t_val = ft_sphere(ref_map, ray);
		else if (ref_map->type == CY)
			closest_t_val = ft_cylinder(ref_map, ray);
		else if (ref_map->type == PL)
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
	return ClosestHit(ray, old_closest, closest_obj);
}

// Reflection=Incident−2×(Normal⋅Incident)×Normal
t_vec3d reflect(t_vec3d incident, t_vec3d normal)
{
    return (t_vec3d_sub(incident, t_vec3d_scale(normal, 2.0f * dot(incident, normal))));
}

#include <stdlib.h>
#include <time.h>

t_vec3d getrendomvec3d(float roughness)
{
	t_vec3d ran_vec;
// int random_number = 1 + rand() % 10
	ran_vec.x = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.y = ((float)rand() / RAND_MAX - 0.5) * roughness;
	ran_vec.z = ((float)rand() / RAND_MAX - 0.5) * roughness;
	return (ran_vec);
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

	t_vec3d colour = (t_vec3d){0,0,0};
	t_vec3d final_colour = (t_vec3d){0,0,0};
	float	multiplier = 1.0f;

	int bounces = 5;
	int i = 0;
	for (i = 0; i < bounces; i++)
	{
		t_hitpayload *payload = TraceRay(rt->hitable, ray);
		if (payload->hit_distance < 0.0f)
		{
			t_vec3d skyColor = init_vec3d(0.0f, 0.0f, 0.0f);
			final_colour = t_vec3d_add(final_colour, t_vec3d_scale(skyColor, multiplier));
			break ;
		}
		t_vec3d hit_point = t_vec3d_add(camera()->pos, payload->raydir);
		t_vec3d normal = t_vec3d_sub(hit_point, payload->obj->point);
		t_vec3d lvec = t_vec3d_sub(light()->pos, hit_point);
		float light_ratio = diffuse_light(normal, lvec);
		light_ratio = specular_light(normal, lvec, t_vec3d_scale(payload->raydir, -1), light_ratio);
		colour = color_multiply(payload->obj->rgb, light_ratio);
		final_colour = t_vec3d_add(final_colour, t_vec3d_scale(colour, multiplier));
		multiplier *= 0.5f;
		ray.orig = t_vec3d_add(payload->world_positoin, t_vec3d_scale(payload->world_normal, 0.0001f));
		t_vec3d randomised = getrendomvec3d(payload->obj->roughness);
		// printf("%f\n", payload->obj->roughness);
		ray.dir = reflect(ray.dir, t_vec3d_add(payload->world_normal, randomised));
	}
	return (final_colour);
}