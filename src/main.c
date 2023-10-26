#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"



// type converts characters into int, e.g. A = 65, pl = 112 + 108.
typedef struct s_map
{
	int		type;
	float	pointq[3];
	float	light;
	int		rgb[3];
	float	normalized_o[3];
	int		fov;
	float	diameter;
} t_map;


int	main(int ac, char **av)
{
	if (ac == 2)
	{
		
	}
}