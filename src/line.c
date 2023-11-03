#include "minirt.h"

void draw_line(t_rt *rt, vec2d p1, vec2d p2, int color)
{
    double dx = fabs(p2.x - p1.x);
    int sx = p1.x < p2.x ? 1 : -1;
    double dy = -fabs(p2.y - p1.y);
    int sy = p1.y < p2.y ? 1 : -1;
    double error = dx + dy;

    while (1)
    {
        put_color_to_pixel(rt, p1.x, p1.y, color);
        if (p1.x == p2.x && p1.y == p2.y)
            break ;
        double e2 = 2 * error;
        if (e2 >= dy)
        {
            if (p1.x == p2.x)
                break;
            error = error + dy;
            p1.x = p1.x + sx;
        }
        if (e2 <= dx)
        {
            if (p1.y == p2.y)
                break ;
            error = error + dx;
            p1.y = p1.y + sy;
        }
    }
}
