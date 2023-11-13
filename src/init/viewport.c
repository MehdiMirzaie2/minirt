#include "minirt.h"

t_viewport	*viewport(void)
{
	static t_viewport	*viewport;

	return (viewport);
}

void	set_viewport(void)
{
	viewport()->width = 1.0;
	viewport()->height = 1.0;
	viewport()->dist = 1.0;
	viewport()->aspect_ratio = (float)SIZE / (float)SIZE;
}
