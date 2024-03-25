#include "fdf.h"

void 	set_dots_volume(t_fdf *fdf, t_map map, double edge_size)
{
	int	col;
	int	row;

	row = 0;
	col = 0;
	while (row < map.rows)
	{
		col = 0;
		while (col < map.columns)
		{
			fdf->dots[row][col].y -= map.z[row][col] * edge_size;
			col++;
		}
		row++;
	}
	return ;
}


t_dot	**malloc_dots(t_map map)
{
	int	count;
	t_dot	**dots;

	count = 0;
	dots = (t_dot **)malloc(map.rows * sizeof(t_dot *));
	if (!dots)
		return (NULL);
	while (count < map.rows)
	{
		dots[count] = (t_dot *)malloc(map.columns * sizeof(t_dot));
		if (!dots[count])
		{
			while (count-- >= 0)
				free(dots[count]);
			free(dots);
			return (NULL);
		}
		count++;
	}
	return (dots);
}

t_dot	**set_dots(t_map map, t_edge edge)
{
	int	row;
	int	col;
	t_dot	**dots;

	row = 0;
	col = 0;
	dots = malloc_dots(map);
	if (!dots)
		return (NULL);
	dots[row][col].x = (WIN_WIDTH - ((map.columns + map.rows - 2) * edge.width)) / 2;
	dots[row][col].y = WIN_HEIGHT - ((map.rows - 1) * edge.height);
	col++;
	while (row < map.rows)
	{
		if (row > 0)
		{
			col = 0;
			dots[row][col].x = dots[row - 1][col].x + edge.width;
			dots[row][col].y = dots[row - 1][col].y + edge.height;
			col++;
		}
		while (col < map.columns)
		{
			dots[row][col].x = dots[row][col - 1].x + edge.width;
			dots[row][col].y = dots[row][col - 1].y - edge.height;
			col++;
		}
		row++;
	}
	return (dots);
}

t_fdf	*set_fdf(t_map map)
{
	t_fdf	*fdf;
	t_edge	*edge;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->mlx = mlx_init();
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
	edge = set_edge(map);
	if (!edge)
		return (NULL);
	fdf->dots = set_dots(map, *edge);
	if (!fdf->dots)
		return (NULL);
	fdf->rows = map.rows;
	fdf->columns = map.columns;
	set_dots_volume(fdf, map, edge->size);
	free(edge);
	return (fdf);
}
