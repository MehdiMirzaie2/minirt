#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"
#include "map.h"

int	main(int ac, char **av)
{
	t_map *map;

	map = NULL;
	if (ac == 2)
	{
		map = malloc(sizeof(t_map));
		ft_read(&map, av[1]);
	}
	return (0);
}