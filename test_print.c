#include "fdf.h"

void	print_tab(t_map *map)
{
	int	count;
	int	count2;

	count = 0;
	while(count < map->rows)
	{
		count2 = 0;
		while(count2 < map->columns)
		{
			printf("%i ", map->z[count][count2]);
			count2++;
		}
		printf("\n");
		count++;
	}
}

void print_dots(t_fdf *fdf)
{
	int	count1;
	int	count2;

	count1 = 0;
	while (count1 < fdf->rows)
	{
		count2 = 0;
		while (count2 < fdf->columns)
		{
			// printf("dot.x: %f | dot.y: %f\n", fdf->dots[count1][count2].x, fdf->dots[count1][count2].y);
			count2++;
		}
		printf("\n");
		count1++;
	}
}

