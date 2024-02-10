#include "fdf.h"
#include "stdio.h"

void	print_tab(t_map *map)
{
	int	count;
	int	count2;

	count = 0;
	while(count < map->ylen)
	{
		count2 = 0;
		while(count2 < map->xlen)
		{
			printf("%i ", map->z[count][count2]);
			count2++;
		}
		printf("\n");
		count++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 2)
	{
		// if (validate(argv[1]) == 0)
		// 	return (1);
		map = generate_map(argv[1]);
		print_tab(map);
	}
	(void)map;
	return (0);
}
