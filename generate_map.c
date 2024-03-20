#include "libft/libft.h"
#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i]) {
		free(split[i]);
		i++;
	}
	free(split);
}

t_map	*malloc_map(char *file)
{
	t_map	*map;

	map = (t_map *)malloc(1 * sizeof(t_map));
	if (!map)
		return (NULL);
	map->rows = get_gnl_len(file);
	map->z = (int **)malloc(map->rows * sizeof(int *));
	if (!map->z)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	*array_atoi(char **split, int size)
{
	int	*nbr_row;
	int	count;
	int	len;

	len = get_array_len(split);
	if (len != size || len < 2)
	{
		free_split(split);
		return (0);
	}
	nbr_row = (int *)malloc(len * sizeof(int));
	count = 0;
	while (split && split[count])
	{
		if (split[count][0] == '\n' || split[count][0] == '\0')
			break ;
		nbr_row[count] = ft_atoi(split[count]);
		free(split[count]);
		count++;
	}
	free(split[count]);
	free(split);
	return (nbr_row);
}

int	fill_map_rows(t_map *map, int fd)
{
	int	count;
	char	*line;

	count = 0;
	while (count < map->rows)
	{
		line = get_next_line(fd);
		if (count == 0)
			map->columns = get_row_len(line);
		map->z[count] = array_atoi(ft_split(line, ' '), map->columns);
		free(line);
		if (map->z[count] == 0)
			return (0);
		count++;
	}
	line = get_next_line(fd);
	if (line)
		free(line);
	return (1);
}

t_map	*generate_map(char *file)
{
	char	*line;
	t_map	*map;
	int	rows;
	int	fd;

	fd = open(file, O_RDONLY);
	map = malloc_map(file);
	if (!map)
		return (NULL);
	rows = fill_map_rows(map, fd);
	if (!rows)
	{
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		free_z(rows + 1, map->z);
		free(map);
		ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
		return (NULL);
	}
	close(fd);
	return (map);
}
