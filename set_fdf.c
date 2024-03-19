#include "fdf.h"

// aplica altura dos pontos, eixo z
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

// define distâncias entre os pontos baseado no tamanho do mapa e janela. retorna em t_edge
t_edge	*set_edge(t_map map)
{
	t_edge *edge;
	int	height_len;
	double	map_width;
	double	map_height;

	height_len = get_height_proportion(map);
	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->height = WIN_HEIGHT / height_len;
	edge->size = edge->height * 2;
	edge->width = get_edge_width(edge->size);
	map_width = (map.columns + map.rows) * edge->width;
	if (map_width > WIN_WIDTH)
	{
		map_height = (WIN_HEIGHT * WIN_WIDTH) / map_width;
		map_width = WIN_WIDTH;
		edge->height = map_height / height_len;
		edge->size = edge->height * 2;
		edge->width = get_edge_width(edge->size);
	}
	return (edge);
}

// malloca matriz de par ordenado
t_dot	**malloc_dots(t_map map)
{
	int	count;
	t_dot	**dots;

	count = 0;
	dots = (t_dot **)malloc(map.rows * sizeof(t_dot *));
	while (count < map.rows)
	{
		dots[count] = (t_dot *)malloc(map.columns * sizeof(t_dot));
		count++;
	}
	return (dots);
}

//	a partir do edge(distância entre pontos) e do mapa, define e retorna a matriz do par ordenado de cada ponto do fdf
t_dot	**set_dots(t_map map, t_edge edge)
{
	int	row;
	int	col;
	t_dot	**dots;

	row = 0;
	col = 0;
	dots = malloc_dots(map);
	// dots[row][col] = get_start(map, edge);
	dots[row][col].x = (WIN_WIDTH - ((map.columns + map.rows) * edge.width)) / 2;
	dots[row][col].y = WIN_HEIGHT - (map.rows * edge.height);
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

// define e retorna(em t_fdf) tudo necessário para renderizar o fdf
t_fdf	*set_fdf(t_map map)
{
	t_fdf	*fdf;
	t_edge	*edge;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	edge = set_edge(map);
	fdf->dots = set_dots(map, *edge);
	fdf->rows = map.rows;
	fdf->columns = map.columns;
	set_dots_volume(fdf, map, edge->size);
	free(edge);
	// free(map);
	return (fdf);
}
