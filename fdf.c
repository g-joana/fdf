#include "fdf.h"
//#include "libft/libft.h"
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

int	validate(char *file)
{
	int	fd;

	if (ft_strstr(file, ".fdf") == NULL)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
/*
int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 2)
	{
		if (validate(argv[1]) == 0)
		 	return (1);
		map = generate_map(argv[1]);
		open_win(500, 500);
		//print_tab(map);
	}
	(void)map;
	return (0);
}
*/
