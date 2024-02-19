#include "libft/libft.h"
#include "fdf.h"

int	gnl_len(char *file)
{
	int	fd;
	int	len;

	len = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd))
		len++;
	close(fd);
	return (len);
}

int	count_tab(char *file)
{
	int	fd;
	int	len;
	char	**split;

	len = 0;
	fd = open(file, O_RDONLY);
	split = ft_split(get_next_line(fd), ' ');
	while (split[len] && (split[len][0] != '\n' || split[len][0] != '\0'))
	{
		if (split[len][0] == '\n' || split[len][0] == '\0')
			break ;
		len++;
	}
	close(fd);
	return (len);
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
	if (len != size)
		return (0);
	atoi_tab = (int *)malloc(len * sizeof(int));
	while (tab && tab[count])
	{
		if (tab[count][0] == '\n' || tab[count][0] == '\0')
			break ;
		atoi_tab[count] = ft_atoi(tab[count]);
		count++;
	}
	count--;
	return (atoi_tab);
}

t_map	*generate_map(char *file)
{
	int	fd;
	int	count;
	t_map	*map;

	count = 0;
	map = (t_map *)malloc(1 * sizeof(t_map));
	map->xlen = count_tab(file);
	fd = open(file, O_RDONLY);
	map->ylen = gnl_len(file);
	map->z = (int **)malloc(map->ylen * sizeof(int *));
	while (count < map->ylen)
	{
		map->z[count] = tab_atoi(ft_split(get_next_line(fd), ' '), map->xlen);
		if (map->z[count] == 0)
		{
			ft_printf("%s\n", "Found wrong line length. Exiting.");
			return (free(map), free(map->z), NULL);
		}
		count++;
	}
	return (map);
}
