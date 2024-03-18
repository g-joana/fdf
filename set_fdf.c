#include "fdf.h"

void 	set_dots_volume(t_fdf *fdf, t_map map, double edge_size)
{
	int	col;
	int	row;

	row = 0;
	col = 0;
	while (row < fdf->rows)
	{
		col = 0;
		while (col < fdf->columns)
		{
			fdf->dots[row][col].y -= map.z[row][col] * edge_size;
			col++;
		}
		row++;
	}
	return ;
}

t_edge	*set_edge(t_map map)
{
	t_edge *edge;
	int	height_len;
	double	map_width;
	double	map_height;

	height_len = get_height_proportion(map);
	edge = (t_edge *)malloc(sizeof(t_edge));
	edge->height = WIN_HEIGHT / height_len;
	edge->size = edge->height * 2;
	edge->width = get_edge_width(edge->size);
	map_width = map.columns + map.rows * edge->width;
	if (map_width > WIN_WIDTH)
	{
		map_height = (WIN_HEIGHT * WIN_WIDTH) / map_width;
		map_width = WIN_WIDTH;
		edge->height = map_height / height_len;
	}
	return (edge);
}

// t_dots	**malloc_dots()

//	a partir do edge_size e do mapa, define o par ordenado de cada ponto do fdf
t_dot	**set_dots(t_fdf fdf, t_map map, t_edge edge)
{
	int	count;
	int	row;
	int	col;
	t_dot	**dots;
	// t_edge	*edge;
	
	// edge = set_edge(map);
	//dots = malloc_dots(map);
	//
	// edge = (t_edge *)malloc(sizeof(t_edge));
	// edge->height = get_edge_height(&map);
	// edge->size = edge->height * 2;
	// // edge->width = edge->height * sqrt(3);
	// edge->width = get_edge_width(edge->size);
	//
	// start = (WIN_WIDTH - (fdf->columns + fdf->rows * (edge / 2)) / 2);
	//map_width = fdf->columns + fdf->rows;
	count = 0;
	dots = (t_dot **)malloc(fdf.rows * sizeof(t_dot *));
	while (count < fdf.rows)
	{
		dots[count] = (t_dot *)malloc(fdf.columns * sizeof(t_dot));
		count++;
	}
	row = 0;
	col = 0;
	//start
	dots[row][col].x = (WIN_WIDTH - ((map.columns + map.rows) * edge.width)) / 2;
	dots[row][col].y = WIN_HEIGHT - (fdf.rows * edge.height);
	col++;
	while (row < fdf.rows)
	{
		if (row > 0)
		{
			col = 0;
			dots[row][col].x = dots[row - 1][col].x + edge.width;
			dots[row][col].y = dots[row - 1][col].y + edge.height;
			col++;
		}
		while (col < fdf.columns)
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

	// edge_size = 2 * get_edge_height(&map);
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	edge = set_edge(map);
	fdf->rows = map.rows;
	fdf->columns = map.columns;
	fdf->dots = set_dots(*fdf, map, *edge);
	set_dots_volume(fdf, map, edge->size);
	return (fdf);
}
