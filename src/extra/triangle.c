#include "minirt.h"

void	draw_triangle(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
{
	t_vec2 p1 = {x1, y1};
	t_vec2 p2 = {x2, y2};
	t_vec2 p3 = {x3, y3};

	printf("x = %d\t y = %d\n", x1, y1);
	printf("x = %d\t y = %d\n", x2, y2);
	printf("x = %d\t y = %d\n\n", x3, y3);
	draw_line(rt, p1, p2, 0x000000);
	draw_line(rt, p2, p3, 0x000000);
	draw_line(rt, p3, p1, 0x000000);
}

void fill_bottomflat_tri(t_rt *rt, t_vec2 v1, t_vec2 v2, t_vec2 v3)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scnalineY = v1.y; scnalineY <= v2.y; scnalineY++)
    {
        draw_line(rt, (t_vec2){(int)curx1, scnalineY}, (t_vec2){(int)curx2, scnalineY}, 0xFFFFFF);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fill_topflat_tri(t_rt *rt, t_vec2 v1, t_vec2 v2, t_vec2 v3)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (int scnalineY = v3.y; scnalineY >= v1.y; scnalineY--)
    {
        draw_line(rt, (t_vec2){(int)curx1, scnalineY}, (t_vec2){(int)curx2, scnalineY}, 0xFFFFFF);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void	swapt_vec2(t_vec2 *v1, t_vec2 *v2)
{
	t_vec2	temp;

	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void	sortVerticesAscendingByY(t_vec2 *v1, t_vec2 *v2, t_vec2 *v3)
{
	if (v1->y > v2->y)
		swapt_vec2(v1, v2);
	if (v2->y > v3->y)
		swapt_vec2(v2, v3);
	if (v1->y > v2->y)
		swapt_vec2(v1, v2);
}

void draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
{
    t_vec2 v1 = {x1, y1};
    t_vec2 v2 = {x2, y2};
    t_vec2 v3 = {x3, y3};

    sortVerticesAscendingByY(&v1, &v2, &v3);

    if (v2.y == v3.y)
        fill_bottomflat_tri(rt, v1, v2, v3);
    else if (v1.y == v2.y)
        fill_topflat_tri(rt, v1, v2, v3);
    else
    {
        t_vec2 v4 = {(int)(v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)), v2.y};
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
// 		draw_line(rt, (t_vec2){x1, y1}, (t_vec2){x2, y2});
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
// 		draw_line(rt, (t_vec2){x1, y1}, (t_vec2){x2, y2});
// 		curx1 -= invslope1;
//     	curx2 -= invslope2;
// 	}
// }

// void	swapt_vec2(t_vec2 *v1, t_vec2 *v2)
// {
// 	t_vec2	temp;

// 	temp = *v1;
// 	*v1 = *v2;
// 	*v2 = temp;
// }

// void	sortVerticesAscendingByY(t_vec2 *v1, t_vec2 *v2, t_vec2 *v3)
// {
// 	if (v1->y > v2->y)
// 		swapt_vec2(v1, v2);
// 	if (v2->y > v3->y)
// 		swapt_vec2(v2, v3);
// 	if (v1->y > v2->y)
// 		swapt_vec2(v1, v2);
// }

// void	draw_fill_tri(t_rt *rt, int x1, int y1, int x2, int y2, int x3, int y3)
// {
// 	t_vec2 v1 = {x1, y1};
// 	t_vec2 v2 = {x2, y2};
// 	t_vec2 v3 = {x3, y3};

// 	sortVerticesAscendingByY(&v1, &v2, &v3);
// 	if (v2.y == v3.y)
// 		fill_bottomflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
// 	else if (y1 == y2)
// 		fill_topflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
// 	else
// 	{
// 		t_vec2 v4 = {(int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1)), y2};
// 		fill_bottomflat_tri(rt, v1.x, v1.y, v2.x, v2.y, v4.x, v4.y);
// 		fill_topflat_tri(rt, v2.x, v2.y, v4.x, v4.y, v3.x, v3.y);
// 	}
// }

