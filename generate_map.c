#include "libft/libft.h"
#include "fdf.h"

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

int	gnl_len(char *file)
{
	int	fd;
	int	len;
	char	*line;

	len = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	get_row_len(char *line)
{
	int	len;
	int	number;

	len = 0;
	number = 0;
	while (line[len] && line[len] != '\n' && line[len] != '\0')
	{
		while (line[len] == ' ')
			len++;
		if (line[len] == '\0' || line[len] == '\n')
			break ;
		while (line[len] != ' ')
		{	
			if (line[len + 1] == '\0' || line[len + 1] == '\n' || line[len + 1] == ' ')
			{	
				len++;
				number++;
				break ;
			}
			len++;
		}
	}
	return (number);
}

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

int	*array_atoi(char **split, int size)
{
	int	*nbr_row;
	int	count;
	int	len;

	len = 0;
	while (split && split[len])
	{
		if (split[len][0] == '\n' || split[len][0] == '\0')
			break ;
		len++;
	}
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

int	fill_map_rows(t_map *map, char *file)
{
	int	fd;
	int	count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	while (count < map->rows)
	{
		line = get_next_line(fd);
		if (count == 0)
			map->columns = get_row_len(line);
		map->z[count] = array_atoi(ft_split(line, ' '), map->columns);
		if (map->z[count] == 0)
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			free_z(count + 1, map->z);
			free(map);
			return (0);
		}
		free(line);
		count++;
	}
	line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
	return (1);
}

t_map	*generate_map(char *file)
{
	t_map	*map;

	if (!validate(file))
	{	
		ft_putstr_fd("Invalid file. Exiting.", 2);
		return (NULL);
	}
	map = (t_map *)malloc(1 * sizeof(t_map));
	map->rows = gnl_len(file);
	map->z = (int **)malloc(map->rows * sizeof(int *));
	if (!fill_map_rows(map, file))
	{
		ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
		return (NULL);
	}
	return (map);
}
