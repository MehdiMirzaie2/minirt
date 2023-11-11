

void test_parser(t_map *map)
{
	while (map)
	{
		if (map->type == 'A')
			printf("A: %f\t %d,%d,%d\n", map->light, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == 'C')
			printf("C: %f,%f,%f\t %f,%f,%f\t %d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->fov);
		if (map->type == 'L')
			printf("L: %f,%f,%f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->brightness, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTSP)
			printf("sp: %f,%f,%f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->diameter, map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTPL)
			printf("pl: %f,%f,%f\t %f,%f,%f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->rgb[0], map->rgb[1], map->rgb[2]);
		if (map->type == E_TTCY)
			printf("cy: %f,%f,%f\t %f,%f,%f\t %f\t %f\t %d,%d,%d\n", map->point[0], map->point[1],
				map->point[2], map->normalized[0], map->normalized[1], map->normalized[2], map->diameter, map->height, map->rgb[0], map->rgb[1], map->rgb[2]);
		map = map->next;
	}
}
