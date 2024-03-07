#include "libft/libft.h"
#include "fdf.h"

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
		printf("len: %i | line: %s\n", len, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	count_gnl_numbers(char *gnl)
{
	int	len;
	int	number;

	len = 0;
	number = 0;
	while (gnl[len] && gnl[len] != '\n' && gnl[len] != '\0')
	{
		while (gnl[len] == ' ')
			len++;
		if (gnl[len] == '\0' || gnl[len] == '\n')
			break ;
		while (gnl[len] != ' ')
		{	
			if (gnl[len + 1] == '\0' || gnl[len + 1] == '\n' || gnl[len + 1] == ' ')
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

int	tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab && tab[len])
	{
		if (tab[len][0] == '\n' || tab[len][0] == '\0')
			break ;
		len++;
	}
	return (len);
}

int	*tab_atoi(char **tab, int size)
{
	int	*atoi_tab;
	int	count;
	int	len;

	count = 0;
	len = tab_len(tab);
	if (size == 0)
		return (0);
	atoi_tab = (int *)malloc(len * sizeof(int));
	while (tab && tab[count])
	{
		if (tab[count][0] == '\n' || tab[count][0] == '\0')
			break ;
		atoi_tab[count] = ft_atoi(tab[count]);
		free(tab[count]);
		count++;
	}
	free(tab);
	return (atoi_tab);
}

t_map	*generate_map(char *file)
{
	int	fd;
	int	count;
	char	*line;
	t_map	*map;

	count = 0;
	map = (t_map *)malloc(1 * sizeof(t_map));
	fd = open(file, O_RDONLY);
	map->rows = gnl_len(file);
	map->z = (int **)malloc(map->rows * sizeof(int *));
	// printf("map rows: %i\n", map->rows);
	line = get_next_line(fd);
	map->columns = count_gnl_numbers(line);
	while (count < map->rows)
	{
		map->z[count] = (int *)malloc(map->columns * sizeof(int));
		map->z[count] = tab_atoi(ft_split(line, ' '), map->columns);
		if (map->z[count] == 0)
		{
			//printf("linha: %i\n", count);
			printf("%s\n", "Found wrong line length. Exiting.");
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
		count++;
	}
	//map->rows = count;
	free(line);
	close(fd);
	return (map);
}
