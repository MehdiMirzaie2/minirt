
#include "minirt.h"

void rotate_x(t_vec3d *coord, t_rt *rt)
{
    float t_y = coord->y;

    coord->x = t_y * cos(rt->fTheta) + coord->z * sin(rt->fTheta);
    coord->z = t_y * -sin(rt->fTheta) + coord->z * cos(rt->fTheta);
}

void rotate_y(t_vec3d *coord, t_rt *rt)
{
    float t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->z*-sin(rt->fTheta);
    coord->z = t_x*sin(rt->fTheta) + coord->z*cos(rt->fTheta);
}

void rotate_z(t_vec3d *coord, t_rt *rt)
{
    float t_x = coord->x;

    coord->x = t_x*cos(rt->fTheta) + coord->y * sin(rt->fTheta);
    coord->y = t_x* -sin(rt->fTheta) + coord->y * cos(rt->fTheta);
}

int ft_cone(t_rt *rt, t_vec3d coord, t_vec2d notnorm)
{
    t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayOrigin = (t_vec3d){-0.8f, 0.0f, rt->zoom};
    rotate_z(&rayDirections, rt);
    // rt->fTheta += 0.01;

    float a = ((rayDirections.x * rayDirections.x) - (rayDirections.y * rayDirections.y) + (rayDirections.z * rayDirections.z));
    float b = 2.0f * (rayOrigin.x * rayDirections.x - rayOrigin.y * rayDirections.y + rayOrigin.z * rayDirections.z);
    float c = ((rayOrigin.x * rayOrigin.x) - (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z));

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
        if (nt > 0.0f)
        {
        t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
        // (void)fulldir;
        t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        t_vec3d normal = hit_point;
        normalize(&normal);
        // normalize(&rt->light_dir);
        // update_light_dir(&rt->light_dir, rt->light_dir.x, rt->light_dir.y);
        t_vec3d ref_light_dir = rt->light_dir;
        // t_vec3d ref_light_dir = (t_vec3d){-1, -1, -1};
        normalize(&ref_light_dir);
        rotate_z(&ref_light_dir, rt);
        // normalize(&ref_light_dir);
        float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, 0xFF0000}));
        }
        return (1);
    }
    else
        return (0);
}

// int ft_cylinder(t_rt *rt, t_vec3d coord, t_vec2d notnorm)
// {
//     t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -5.0f};
//     t_vec3d rayOrigin = (t_vec3d){0.4f, 0.0f, rt->zoom};
//     // rotate_z(&rayDirections, rt);

//     float a = ((rayDirections.x * rayDirections.x) + (rayDirections.z * rayDirections.z));
//     float b = 2.0f * (rayOrigin.x * rayDirections.x + rayOrigin.z * rayDirections.z);
//     float c = -1.0f;

//     float discriminant = b * b - 4.0f * a * c;
//     if (discriminant >= 0.0f)
//     {
//         float t = (-b + sqrt(discriminant)) / (2.0f * a);
//         (void)t;
//         float nt = (-b - sqrt(discriminant)) / (2.0f * a);

//         t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
//         // (void)fulldir;
//         t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
//         t_vec3d normal = hit_point;
//         normalize(&normal);
//         // update_light_dir(&rt->light_dir, rt->light_dir.x, rt->light_dir.y);
//         t_vec3d ref_light_dir = rt->light_dir;
//         normalize(&ref_light_dir);
//         float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
//         put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, 0xFF0000}));
//         return (1);
//     }
//     else
//         return (0);
// }

void    printvec3(t_vec3d vec)
{
    printf("%f\t%f\t%f\n", vec.x, vec.y, vec.z);
}

void ft_draw_light(t_rt *rt)
{
    // printf("im light\n");
    normalize(&rt->light_dir);
    rt->light_dir.x += SIZE / 2;
    rt->light_dir.y += SIZE / 2;
    put_color_to_pixel(rt, rt->light_dir.x + 1, rt->light_dir.y + 1, 0xffffff);
    put_color_to_pixel(rt, rt->light_dir.x + 1, rt->light_dir.y + 1, 0xffffff);
    put_color_to_pixel(rt, rt->light_dir.x - 1, rt->light_dir.y - 1, 0xffffff);
    put_color_to_pixel(rt, rt->light_dir.x - 1, rt->light_dir.y - 1, 0xffffff);
    put_color_to_pixel(rt, rt->light_dir.x, rt->light_dir.y, 0xffffff);
    put_color_to_pixel(rt, rt->light_dir.x, rt->light_dir.y, 0xffffff);
}

int ft_sphere(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d rayDirections = (t_vec3d){coord.x, coord.y, -1.0f};
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom};
    float radius = 0.5f;

    float a = dot(rayDirections, rayDirections);
    float b = 2.0f * dot(rayOrigin, rayDirections);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0.0f)
    {
        float t = (-b + sqrt(discriminant)) / (2.0f * a);
        (void)t;
        float nt = (-b - sqrt(discriminant)) / (2.0f * a);
        if (nt > 0.0f)
        {
        t_vec3d fulldir = t_vec3d_scale(rayDirections, nt);
        // (void)fulldir;

        t_vec3d hit_point = t_vec3d_add(rayOrigin, t_vec3d_scale(rayDirections, nt));
        t_vec3d normal = hit_point;
        normalize(&normal);
        // update_light_dir(&rt->light_dir, rt->light_dir.x, rt->light_dir.y);
        t_vec3d ref_light_dir = (t_vec3d){-1, -1, -1};
        normalize(&ref_light_dir);
        // normalize(&ref_light_dir);
        // float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
        float intensity = max(dot(normal, t_vec3d_scale(ref_light_dir, -1)), 0.0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, ConvertToRGBA((t_vec3d){intensity, intensity, intensity}));
        }
    }
    else if (ft_cone(rt, (t_vec3d){coord.x, coord.y, -1.0}, notnorm) == 0)
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
        // ft_draw_light(rt);
        // if (ft_cylinder(rt, (t_vec3d){coord.x, coord.y, -1.0}, notnorm) == 0)
            return (0);
    return (1);
}

// bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
// {
//     // assuming vectors are all normalized
//     float denom = dotProduct(n, l);
//     if (denom > 1e-6)
//     {
//         Vec3f p0l0 = p0 - l0;
//         t = dotProduct(p0l0, n) / denom;
//         return (t >= 0);
//     }

//     return false;
// }

// void plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
// {
//     t_vec3d point_on_plane = (t_vec3d){0, 0, -10.0}; // n
//     t_vec3d normal = (t_vec3d){0, 1, 0}; // p0
//     t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
//     t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


//     float denom = dot(normal, l);
//     if (denom > 1e-6)
//     {
//         // t_vec3d p0l0 = normal - rayOrigin;
//         t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
//         float t = dot(p0l0, point_on_plane) / denom;
//         // return (t >= 0);
//         put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x1000ff00);
//     }
//     // else if (ft_sphere(rt, coord, notnorm) == 0)
//     // else
//         // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
// }

void plane(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    t_vec3d normal = (t_vec3d){0, 0, -1}; // p0
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        // t_vec3d p0l0 = normal - rayOrigin;
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        // return (t >= 0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0xf9f1f0);
    }
    // else if (ft_sphere(rt, coord, notnorm) == 0)
    // else
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
}

void plane2(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    t_vec3d normal = (t_vec3d){1, 0, 0}; // p0
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        // t_vec3d p0l0 = normal - rayOrigin;
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        // return (t >= 0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0xfadcd9);
    }
    // else if (ft_sphere(rt, coord, notnorm) == 0)
    // else
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
}

void plane3(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    t_vec3d normal = (t_vec3d){0, 1, 0}; // p0
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        // t_vec3d p0l0 = normal - rayOrigin;
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        // return (t >= 0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0xf8afa6);
    }
    // else if (ft_sphere(rt, coord, notnorm) == 0)
    // else
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
}

void plane4(t_rt *rt, t_vec2d coord, t_vec2d notnorm)
{
    t_vec3d point_on_plane = (t_vec3d){0.0, 3.5, 0.0}; // n
    t_vec3d normal = (t_vec3d){0, -1, 0}; // p0
    t_vec3d rayOrigin = (t_vec3d){0.0f, 0.0f, rt->zoom}; // l0
    t_vec3d l = (t_vec3d){coord.x, coord.y, -1.0f};


    float denom = dot(normal, l);
    if (denom > 1e-6)
    {
        // t_vec3d p0l0 = normal - rayOrigin;
        t_vec3d p0l0 = t_vec3d_sub(normal, rayOrigin);
        float t = dot(p0l0, point_on_plane) / denom;
        // return (t >= 0);
        put_color_to_pixel(rt, notnorm.x, notnorm.y, 0xf79489);
    }
    // else if (ft_sphere(rt, coord, notnorm) == 0)
    // else
        // put_color_to_pixel(rt, notnorm.x, notnorm.y, 0x10000000);
}