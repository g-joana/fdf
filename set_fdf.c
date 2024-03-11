#include "fdf.h"

//	calcula  (em quantidade de edge_h)
int	get_height_proportion(t_map map)
{
	int	y;
	int	x;
	int	highest_h;
	int	lowest_h;
	int	vol;

	highest_h = map.columns;
	lowest_h = -map.rows;
	vol = 0;
	y = 0;
	while (y < map.rows)
	{
		x = 0;
		while (x < map.columns)
		{
			vol = (map.z[y][x] * 2) + x - y;
			// cada edge da base tem h de altura e cada edge vertical tem 2h de altura.
			// cada vez que o x aumenta, o volume aumenta junto.
			// aumentar: aumentar seria subir(-) na tela(eixo y), pois sua origem mudaria.
			// por fim, o volume sobreescreve o volume inicial (so a base) contando com os relevos, caso tenha algum que passe essa altura
			if (vol > highest_h)
				highest_h = vol;
			if (vol < lowest_h)
				lowest_h = vol;
			x++;
		}
		y++;
		vol = -y;
	}
	return (highest_h - lowest_h);
}

double	get_edge_width(double edge_size)
{
	double	edge_width;
	double	radians;

	radians = 30.0 * (M_PI / 180.0);
	edge_width = edge_size / cos(radians);

	return (edge_width);
}

double	get_edge_height(t_map *map)
{	
	double	edge_h;
	double	edge_width;
	int	height_len;
	double	proportion;

	height_len = get_height_proportion(*map);
	edge_h = WIN_HEIGHT / height_len;
	edge_width = get_edge_width(edge_h * 2);
	map->width = sqrt(pow((map->columns * (edge_width)), 2) + pow((map->rows * (edge_width)), 2)); 
	// map->width = map->columns * edge_width + map->rows * edge_width; 
	//raiz de (map.columns * edge_size) ao 2 + (map.rows * edge_size) ao 2;
	if (map->width > WIN_WIDTH)
	{
		proportion = map->width / WIN_WIDTH;
		map->width = map->width / proportion;
		map->new_height = WIN_HEIGHT / proportion;
		edge_h = map->new_height / height_len;
	}
	return (edge_h);
}

// hipotenusa = edge size
// cateto op = edge height
// cateto adj = edge width
// angulo - 30 graus
/*
void	get_edge_size(t_edge *edge)
{
	double radians;

	radians = 30.0 * (M_PI / 180.0);
	edge->size = edge->height / sin(radians);
	// printf("30 * (%f / 180) = %f\n", M_PI, radians);
	// printf("edge->size = %f / %f\n", edge->height, sin(radians));
}
*/
void 	set_dots_volume(t_fdf *fdf, t_map map, t_edge edge)
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
			fdf->dots[row][col].y -= map.z[row][col] * edge.size;
			col++;
		}
		row++;
	}
	return ;
}

//	a partir do edge_size e do mapa, define o par ordenado de cada ponto do fdf
t_dot	**set_dots(t_fdf fdf, t_map map, t_edge *edge)
{
	int	count;
	// int	start;
	int	row;
	int	col;
	t_dot	**dots;
	
	edge->height = get_edge_height(&map);
	edge->size = edge->height * 2;
	edge->width = edge->height * sqrt(3);
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
	dots[row][col].x = (WIN_WIDTH - map.width) / 2;
	dots[row][col].y = WIN_HEIGHT - (fdf.rows * edge->height);
	col++;
	while (row < fdf.rows)
	{
		if (row > 0)
		{
			col = 0;
			dots[row][col].x = dots[row - 1][col].x + edge->width;
			dots[row][col].y = dots[row - 1][col].y + edge->height;
			col++;
		}
		while (col < fdf.columns)
		{
			dots[row][col].x = dots[row][col - 1].x + edge->width;
			dots[row][col].y = dots[row][col - 1].y - edge->height;
			col++;
		}
		row++;
	}
	return (dots);
}
