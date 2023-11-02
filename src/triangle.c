#include "minirt.h"
#include <mlx.h>

void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
{
	vec2d p1 = {x1, y1};
	vec2d p2 = {x2, y2};
	vec2d p3 = {x3, y3};

	printf("x = %d\t y = %d\n", x1, y1);
	printf("x = %d\t y = %d\n", x2, y2);
	printf("x = %d\t y = %d\n\n", x3, y3);
	draw_line(rt, p1, p2);
	draw_line(rt, p2, p3);
	draw_line(rt, p3, p1);
}

void fill_bottomflat_tri(t_rt *rt, vec2d v1, vec2d v2, vec2d v3)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scnalineY = v1.y; scnalineY <= v2.y; scnalineY++)
    {
        draw_line(rt, (vec2d){(int)curx1, scnalineY}, (vec2d){(int)curx2, scnalineY});
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fill_topflat_tri(t_rt *rt, vec2d v1, vec2d v2, vec2d v3)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (int scnalineY = v3.y; scnalineY >= v1.y; scnalineY--)
    {
        draw_line(rt, (vec2d){(int)curx1, scnalineY}, (vec2d){(int)curx2, scnalineY});
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void	swapvec2d(vec2d *v1, vec2d *v2)
{
	vec2d	temp;

	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void	sortVerticesAscendingByY(vec2d *v1, vec2d *v2, vec2d *v3)
{
	if (v1->y > v2->y)
		swapvec2d(v1, v2);
	if (v2->y > v3->y)
		swapvec2d(v2, v3);
	if (v1->y > v2->y)
		swapvec2d(v1, v2);
}

void draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
{
    vec2d v1 = {x1, y1};
    vec2d v2 = {x2, y2};
    vec2d v3 = {x3, y3};

    sortVerticesAscendingByY(&v1, &v2, &v3);

    if (v2.y == v3.y)
        fill_bottomflat_tri(rt, v1, v2, v3);
    else if (v1.y == v2.y)
        fill_topflat_tri(rt, v1, v2, v3);
    else
    {
        vec2d v4 = {(int)(v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)), v2.y};
        fill_bottomflat_tri(rt, v1, v2, v4);
        fill_topflat_tri(rt, v2, v4, v3);
    }
}


// void	fill_bottomflat_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
// {
// 	float	invslope1 = (x2 - x1) / (y2 - y1);
// 	float	invslope2 = (x3 - x1) / (y3 - y1);

// 	float	curx1 = x1;
// 	float	curx2 = x1;

// 	for (int scnalineY = y1; scnalineY <= y2; scnalineY++)
// 	{
// 		draw_line(rt, (vec2d){x1, y1}, (vec2d){x2, y2});
// 		curx1 += invslope1;
//     	curx2 += invslope2;
// 	}
// }

// void	fill_topflat_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
// {
// 	float	invslope1 = (x3 - x1) / (y3 - y1);
// 	float	invslope2 = (x3 - x2) / (y3 - y2);

// 	float	curx1 = x3;
// 	float	curx2 = x3;

// 	for (int scnalineY = y3; scnalineY <= y1; scnalineY--)
// 	{
// 		draw_line(rt, (vec2d){x1, y1}, (vec2d){x2, y2});
// 		curx1 -= invslope1;
//     	curx2 -= invslope2;
// 	}
// }

// void	swapvec2d(vec2d *v1, vec2d *v2)
// {
// 	vec2d	temp;

// 	temp = *v1;
// 	*v1 = *v2;
// 	*v2 = temp;
// }

// void	sortVerticesAscendingByY(vec2d *v1, vec2d *v2, vec2d *v3)
// {
// 	if (v1->y > v2->y)
// 		swapvec2d(v1, v2);
// 	if (v2->y > v3->y)
// 		swapvec2d(v2, v3);
// 	if (v1->y > v2->y)
// 		swapvec2d(v1, v2);
// }

// void	draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
// {
// 	vec2d v1 = {x1, y1};
// 	vec2d v2 = {x2, y2};
// 	vec2d v3 = {x3, y3};

// 	sortVerticesAscendingByY(&v1, &v2, &v3);
// 	if (v2.y == v3.y)
// 		fill_bottomflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
// 	else if (y1 == y2)
// 		fill_topflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
// 	else
// 	{
// 		vec2d v4 = {(int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1)), y2};
// 		fill_bottomflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v4.x, v4.y);
// 		fill_topflat_tri(rt, v2.x, v2.y, v4.x, v4.y, v3.x, v3.y);
// 	}
// }
